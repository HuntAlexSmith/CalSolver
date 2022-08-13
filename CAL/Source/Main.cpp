//*****************************************************************************
//	File:	Main.cpp
//	Author: Hunter Smith
//	Date:	08/05/2022
//	Description:
//		This is main, where all the magic starts
//*****************************************************************************

#include <iostream>
#include "Renderer.h"

// Background Red Color
static float redVal = 1.0f;
static bool redDec = true;

// Background Blue Color
static float blueVal = 1.0f;
static bool blueDec = true;

// Background Green Color
static float greenVal = 1.0f;
static bool greenDec = true;

// Helper function for updating colors
void UpdateColors(float*, bool*, float);

// Delta Time
Uint32 lastTick = 0;
Uint32 curTick = 0;
float dt = 0;

// Main
int main(int argc, char* argv[]) {

	// Make sure renderer exists
	Renderer myRenderer;

	// Initialize the renderer
	myRenderer.Initialize();

	// Create objects here
	Object* testObject = new Object();
	testObject->AddPosition(GfxMath::Point2D(0, 0));
	testObject->AddPosition(GfxMath::Point2D(0, 1));
	testObject->AddPosition(GfxMath::Point2D(1, 1));
	testObject->SetTint(glm::vec3(1.0f, 0.4f, 0.5f));
	// testObject->SetAlpha(0.1f);

	while (myRenderer.IsRunning())
	{
		// Calculate dt
		lastTick = curTick;
		curTick = SDL_GetTicks();
		dt = (curTick - lastTick) / 1000.0f;
		glm::clamp(dt, 0.0f, 0.125f);

		// Update background color
		UpdateColors(&redVal, &redDec, 0.001f);
		UpdateColors(&greenVal, &greenDec, 0.002f);
		UpdateColors(&blueVal, &blueDec, 0.003f);

		// Set background color
		myRenderer.SetBackColor(redVal, greenVal, blueVal);

		// Render objects here
		myRenderer.Render(testObject);

		// Update the renderer
		myRenderer.Update(dt);
	}

	// Remember to delete all objects
	delete testObject;

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
