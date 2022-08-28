//*****************************************************************************
//	Filename: Renderer.cpp
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This file is the Renderer class, which will handle the initialization
//		of OpenGL and SDL, as well as handle any rendering of meshes that are
//		necessary for rendering things
//*****************************************************************************

#include "Renderer.h"
#include "Mesh.h"
#include "GfxMath.h"
#include <iostream>

//*****************************************************************************
//	Description
//		Constructor for the Renderer class
//*****************************************************************************
Renderer::Renderer() : window_(nullptr)
	, width_(1280)
	, height_(720)
	, glContext_(nullptr)
	, backColor_(1)
	, isRunning_(false)
	, inputEvent_()
	, squareVao_(0)
	, shader_(nullptr)
	, camera_(Camera(15.0f, 1280.0f/720.0f, GfxMath::Point2D(3, 3)))
	, renderQueue_()
	, lmbIsClicked(false)
{
}

//*****************************************************************************
//	Description
//		Destructor for the Renderer class
//*****************************************************************************
Renderer::~Renderer()
{
}

//*****************************************************************************
//	Description
//		Initializes the Renderer object
//*****************************************************************************
void Renderer::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize" << std::endl;
		return;
	}

	// Window Attribs
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Depth Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Creating the Window
	window_ = SDL_CreateWindow("CAL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width_,
		height_,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Error handle for window failing to be created
	if (!window_)
	{
		std::cout << "window failed to be created" << std::endl;
		SDL_Quit();
		return;
	}

	// Create an OpenGL Context
	glContext_ = SDL_GL_CreateContext(window_);

	// Error handling
	if (!glContext_)
	{
		std::cout << "failed to create gl context" << std::endl;
		SDL_DestroyWindow(window_);
		SDL_Quit();
		return;
	}
	
	// Load OpenGL
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "failed to load OpenGL" << std::endl;
		SDL_GL_DeleteContext(glContext_);
		SDL_DestroyWindow(window_);
		SDL_Quit();
		return;
	}

	// Set Viewport size
	glViewport(0, 0, width_, height_);

	// Create the shader to use for rendering
	shader_ = new Shader("Data/shader.vert", "Data/shader.frag");
	if (shader_->Failed())
	{
		Shutdown();
		return;
	}

	// Set is running to true, everything initialized
	isRunning_ = true;

	// Now create the square mesh that we will use for everything
	Mesh myMesh;

	// Add vertices
	myMesh.AddVertex(GfxMath::Point2D(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f));
	myMesh.AddVertex(GfxMath::Point2D(0.5f, -0.5f), glm::vec2(1.0f, 0.0f));
	myMesh.AddVertex(GfxMath::Point2D(0.5f, 0.5f), glm::vec2(1.0f, 1.0f));
	myMesh.AddVertex(GfxMath::Point2D(-0.5f, 0.5f), glm::vec2(0.0f, 1.0f));

	// Add Faces
	myMesh.AddFace(0, 1, 2);
	myMesh.AddFace(0, 2, 3);

	// The Vertex, Texture, and Element Buffer Objects
	GLuint vbo, tbo, ebo;

	// Create and upload data to the Vertex Buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * myMesh.GetVertexCount(), myMesh.GetVertices(), GL_STATIC_DRAW);

	// Create and upload data to the Texture Buffer
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * myMesh.GetVertexCount(), myMesh.GetUV(), GL_STATIC_DRAW);

	// Create and upload data to the Element Buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Mesh::Face) * myMesh.GetFaceCount(), myMesh.GetFaces(), GL_STATIC_DRAW);

	// Now create and bind necessary things to the VAO
	glGenVertexArrays(1, &squareVao_);
	glBindVertexArray(squareVao_);

	// Get Position Attrib and enable it
	GLint posAttrib = shader_->GetAttribLocation("position");
	if (posAttrib < 0) {
		std::cout << "Failed to find attribute" << std::endl;
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	// Get tex coord attrib and enable it
	GLint texAttrib = shader_->GetAttribLocation("texcoord");
	if (texAttrib < 0) {
		std::cout << "Failed to find attribute" << std::endl;
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(texAttrib);

	// Remember to bind the ebo before finishing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Unbind the Vertex Array
	glBindVertexArray(0);
}

//*****************************************************************************
//	Description
//		Updates the Renderer, rendering anything that has been requested to
//		be rendered and processing inputs
// 
//	Param dt
//		Delta time in between the last and current frame
//*****************************************************************************
void Renderer::Update(float dt)
{
	if (lmbIsClicked)
		lmbIsClicked = false;

	// Process inputs from user
	while (SDL_PollEvent(&inputEvent_))
	{
		if (inputEvent_.type == SDL_QUIT)
			isRunning_ = false;

		if (inputEvent_.button.type == SDL_MOUSEBUTTONDOWN) {
			if (inputEvent_.button.button == SDL_BUTTON_LEFT) {
				lmbIsClicked = true;
			}
		}
	}

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Remember to use the program
	shader_->Use();

	// Get Uniforms and upload values
	GLint uObjToWorld = shader_->GetUniformLocation("objToWorld");
	GLint uWorldToCam = shader_->GetUniformLocation("worldToCam");
	GLint uCamToNDC = shader_->GetUniformLocation("camToNDC");
	GLint uTint = shader_->GetUniformLocation("tint");
	GLint uAlpha = shader_->GetUniformLocation("alpha");
	GLint uSampler = shader_->GetUniformLocation("usamp");

	// Check for a texture to render

	while (!renderQueue_.empty()) {
		// Get the current data
		RenderData curData = renderQueue_.front();
		renderQueue_.pop();

		// Check for texture
		Texture* tex = curData.texture;
		if (tex) {
			glBindTexture(GL_TEXTURE_2D, tex->TexGL());
		}
		else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// Upload Uniforms
		glUniformMatrix4fv(uObjToWorld, 1, false, &curData.objToWorld[0][0]);
		glUniformMatrix4fv(uWorldToCam, 1, false, &camera_.WorldToCam()[0][0]);
		glUniformMatrix4fv(uCamToNDC, 1, false, &camera_.CamToNDC()[0][0]);
		glUniform3fv(uTint, 1, &curData.tint[0]);
		glUniform1f(uAlpha, curData.alpha);

		// Do the render
		glBindVertexArray(squareVao_);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	// Assert just in case
	assert(glGetError() == GL_NO_ERROR);

	// Swap buffers
	SDL_GL_SwapWindow(window_);
}

//*****************************************************************************
//	Description
//		Shuts the Renderer down
//*****************************************************************************
void Renderer::Shutdown()
{
	// Delete the vao
	if (squareVao_)
		glDeleteVertexArrays(1, &squareVao_);

	// Remember to delete the shader
	delete shader_;

	// Delete context, destroy window, and quit SDL
	if(glContext_)
		SDL_GL_DeleteContext(glContext_);

	if(window_)
		SDL_DestroyWindow(window_);

	SDL_Quit();

	isRunning_ = false;
}

//*****************************************************************************
//	Description
//		Sets the background color of the renderer
// 
//	Param r
//		The red value to set the background to
// 
//  Param g
//		The green value to set the background to
// 
//  Param b
//		The blue value to set the background to
//*****************************************************************************
void Renderer::SetBackColor(float r, float g, float b)
{
	backColor_.r = r;
	backColor_.g = g;
	backColor_.b = b;
	glClearColor(r, g, b, 1.0f);
}

//*****************************************************************************
//	Description
//		Getter for the current status of the renderer
// 
//	Return
//		True if the renderer is running, false otherwise
//*****************************************************************************
bool Renderer::IsRunning()
{
	return isRunning_;
}

void Renderer::Render(Object* obj)
{
	glm::vec4 worldPos = obj->GetWorldPos();
	int posCount = obj->GetPosCount();
	const glm::vec4* positions = obj->GetPos();
	const glm::vec3 tint = obj->GetTint();
	float alpha = obj->GetAlpha();
	Texture* tex = obj->GetTexture();
	for (int i = 0; i < posCount; ++i)
	{
		glm::mat4 oTW = glm::mat4(1);
		oTW[3][0] = worldPos.x + positions[i].x;
		oTW[3][1] = worldPos.y + positions[i].y;
		RenderData dataToAdd;
		dataToAdd.objToWorld = oTW;
		dataToAdd.position = positions[i];
		dataToAdd.tint = tint;
		dataToAdd.alpha = alpha;
		dataToAdd.texture = tex;
		renderQueue_.push(dataToAdd);
	}
}

bool Renderer::GetMouseState(float* x, float* y)
{
	// Get the window coordinates of the mouse
	int xPos;
	int yPos;
	SDL_GetMouseState(&xPos, &yPos);

	// Screen coords to NDC
	glm::mat4 screenToNDC = glm::mat4(
		2.0f / width_, 0, 0, 0,
		0, -2.0f / height_, 0, 0,
		0, 0, 1, 0,
		-1, 1, 0, 1
	);

	// NDC to Camera
	glm::mat4 ndcToCam = GfxMath::AffineInverse(camera_.CamToNDC());

	// Camera to World
	glm::mat4 camToWorld = camera_.CamToWorld();

	// Apply math to the positions
	glm::vec4 worldPos = GfxMath::Point2D(xPos, yPos);
	worldPos = camToWorld * ndcToCam * screenToNDC * worldPos;
	*x = worldPos.x;
	*y = worldPos.y;

	return lmbIsClicked;
}
