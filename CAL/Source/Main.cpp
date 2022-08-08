//*****************************************************************************
//	File:	Main.cpp
//	Author: Hunter Smith
//	Date:	08/05/2022
//	Description:
//		This is main, where all the magic starts
//*****************************************************************************

#include <iostream>
#include "Renderer.h"

static float redVal = 1.0f;
static bool redDec = true;

static float blueVal = 1.0f;
static bool blueDec = true;

static float greenVal = 1.0f;
static bool greenDec = true;

void UpdateColors(float*, bool*, float);

int main(int argc, char* argv[]) {

	// Make sure renderer exists
	Renderer myRenderer;

	// Initialize the renderer
	myRenderer.Initialize();

	while (myRenderer.IsRunning())
	{
		// Update background color
		UpdateColors(&redVal, &redDec, 0.001f);
		UpdateColors(&greenVal, &greenDec, 0.002f);
		UpdateColors(&blueVal, &blueDec, 0.003f);

		// Set background color
		myRenderer.SetBackColor(redVal, greenVal, blueVal);

		// Update the renderer
		myRenderer.Update(0.0f);
	}

	// Remember to shutdown renderer
	myRenderer.Shutdown();

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
