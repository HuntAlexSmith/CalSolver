//*****************************************************************************
//	Filename: Renderer.cpp
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This file is the Renderer class, which will handle the initialization
//		of OpenGL and SDL, as well as handle any rendering of meshes that are
//		necessary for rendering things
//*****************************************************************************
#pragma once

#include "SDLi/SDL.h"
#include "glm/glm.hpp"

class Renderer {
public:
	// Constructor and destructor of the renderer
	Renderer();
	~Renderer();

	// Member functions
	void Initialize();
	void Update(float dt);
	void Shutdown();
	bool IsRunning();

private:
	// SDL things
	SDL_Window* window_;
	int width_;
	int height_;
	SDL_GLContext glContext_;

	// Background Color
	glm::vec3 backColor_;

	// Is Running Check
	bool isRunning_;
};