//*****************************************************************************
//	Filename: Renderer.h
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This file is the Renderer class, which will handle the initialization
//		of OpenGL and SDL, as well as handle any rendering of meshes that are
//		necessary for rendering things
//*****************************************************************************
#pragma once

#include "Camera.h"
#include "Object.h"
#include "Shader.h"
#include "SDLi/SDL.h"
#include "glm/glm.hpp"
#include <queue>

class Renderer {
public:
	// Render Data
	struct RenderData {
		glm::mat4 objToWorld;
		glm::vec4 position;
		glm::vec3 tint;
		float alpha;

		RenderData() :
			objToWorld(glm::mat4(1))
			, position(glm::vec4(0))
			, tint(glm::vec3(0))
			, alpha(1.0f)
		{}

		RenderData(glm::mat4 oTW, glm::vec4 pos, glm::vec3 t, float a) :
			objToWorld(oTW)
			, position(pos)
			, tint(t)
			, alpha(a)
		{}
	};

	// Constructor and destructor of the renderer
	Renderer();
	~Renderer();

	// Member functions
	void Initialize();
	void Update(float dt);
	void Shutdown();

	void SetBackColor(float r, float g, float b);
	bool IsRunning();

	void Render(Object* obj);

private:
	// SDL things
	SDL_Window* window_;
	int width_;
	int height_;
	SDL_GLContext glContext_;
	SDL_Event inputEvent_;

	// Background Color
	glm::vec3 backColor_;

	// Is Running Check
	bool isRunning_;

	// We will only have one mesh, so we can just render that
	GLuint squareVao_;

	// Shader to use for rendering
	Shader* shader_;

	// Camera for rendering
	Camera camera_;

	// Render queue
	std::queue<RenderData> renderQueue_;
};
