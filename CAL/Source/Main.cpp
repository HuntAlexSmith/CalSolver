//*****************************************************************************
//	File:	Main.cpp
//	Author: Hunter Smith
//	Date:	08/05/2022
//	Description:
//		This is main, where all the magic starts
//*****************************************************************************

#include <iostream>
#include "SDLi/SDL.h"
#include "glad/glad.h"

static SDL_Window* window = nullptr;
static SDL_GLContext glContext = nullptr;

static int width = 1280;
static int height = 720;

static float redVal = 1.0f;
static bool redDec = true;

static float blueVal = 1.0f;
static bool blueDec = true;

static float greenVal = 1.0f;
static bool greenDec = true;

void UpdateColors(float*, bool*, float);

int main(int argc, char* argv[]) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize" << std::endl;
		return -1;
	}
	SDL_GL_LoadLibrary(nullptr);

	// Window Attribs
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Depth Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create the Window
	window = SDL_CreateWindow("CAL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!window)
	{
		std::cout << "window failed to be created" << std::endl;
		SDL_Quit();
		return -1;
	}

	// Create OpenGL Context
	glContext = SDL_GL_CreateContext(window);
	if (!glContext)
	{
		std::cout << "failed to create gl context" << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Load OpenGL
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "failed to load OpenGL" << std::endl;
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Set Viewport size
	glViewport(0, 0, width, height);

	// Process Window Events
	SDL_Event inputEvent;
	bool quit = false;
	while (!quit)
	{
		if (SDL_PollEvent(&inputEvent))
			if (inputEvent.type == SDL_QUIT)
				quit = true;

		UpdateColors(&redVal, &redDec, 0.001f);
		UpdateColors(&greenVal, &greenDec, 0.002f);
		UpdateColors(&blueVal, &blueDec, 0.003f);
		glClearColor(redVal, greenVal, blueVal, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	// Remember to destroy and quit SDL before finished
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void UpdateColors(float* colorVal, bool* colorDec, float value)
{
	if (*colorDec)
	{
		*colorVal -= value;
		if (*colorVal < 0.0f)
			*colorDec = false;
	}
	else
	{
		*colorVal += value;
		if (*colorVal > 1.0f)
			*colorDec = true;
	}
}
