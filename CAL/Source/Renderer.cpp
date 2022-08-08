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
#include "glad/glad.h"
#include <iostream>

Renderer::Renderer() : window_(nullptr)
	, width_(1280)
	, height_(720)
	, glContext_(nullptr)
	, backColor_(1)
	, isRunning_(false)
	, inputEvent_()
{
}

Renderer::~Renderer()
{
}

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

	// Set is running to true, everything initialized
	isRunning_ = true;
}

void Renderer::Update(float dt)
{
	// Process inputs from user
	while (SDL_PollEvent(&inputEvent_))
	{
		if (inputEvent_.type == SDL_QUIT)
			isRunning_ = false;
	}

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Render things here


	// Swap buffers
	SDL_GL_SwapWindow(window_);
}

void Renderer::Shutdown()
{
	// Delete context, destroy window, and quit SDL
	SDL_GL_DeleteContext(glContext_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Renderer::SetBackColor(float r, float g, float b)
{
	backColor_.r = r;
	backColor_.g = g;
	backColor_.b = b;
	glClearColor(r, g, b, 1.0f);
}

bool Renderer::IsRunning()
{
	return isRunning_;
}
