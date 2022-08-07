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

Renderer::Renderer() : window_(nullptr)
	, width_(1280)
	, height_(720)
	, glContext_(nullptr)
	, backColor_(1)
	, isRunning_(false)
{
}

Renderer::~Renderer()
{
}

// Member functions
void Renderer::Initialize()
{

}

void Renderer::Update(float dt)
{

}

void Renderer::Shutdown()
{

}

bool Renderer::IsRunning()
{
	return isRunning_;
}
