//*****************************************************************************
//	File:	Main.cpp
//	Author: Hunter Smith
//	Date:	08/05/2022
//	Description:
//		This is main, where all the magic starts
//*****************************************************************************

#include <iostream>
#include "Renderer.h"
#include "Solver.h"

// Background Red Color
static float redVal = 1.0f;
static bool redDec = true;

// Background Blue Color
static float blueVal = 1.0f;
static bool blueDec = true;

// Background Green Color
static float greenVal = 1.0f;
static bool greenDec = true;

// Delta Time
Uint32 lastTick = 0;
Uint32 curTick = 0;
float dt = 0;

// All textures
std::vector<Texture*> textures;

// Main
int main(int argc, char* argv[]) {

	// Make sure renderer exists
	Renderer myRenderer;

	// Make sure the solver exists
	Solver mySolver;

	// Initialize the renderer
	myRenderer.Initialize();

	// Initialize the solver
	mySolver.Initialize();

	// Create objects here

	// Set background color
	myRenderer.SetBackColor(0.5f, 0.5f, 0.5f);

	while (myRenderer.IsRunning())
	{
		// Calculate dt
		lastTick = curTick;
		curTick = SDL_GetTicks();
		dt = (curTick - lastTick) / 1000.0f;
		glm::clamp(dt, 0.0f, 0.125f);

		// Get all the tiles
		Object** boardTiles = mySolver.GetBoard();
		int tileCount = mySolver.GetBoardCount();
		for (int i = 0; i < tileCount; ++i) {
			myRenderer.Render(boardTiles[i]);
		}

		// Get all the pieces
		Object** pieces = mySolver.GetPieces();
		int pieceCount = mySolver.GetPieceCount();
		for (int i = 0; i < pieceCount; ++i) {
			myRenderer.Render(pieces[i]);
		}

		// Render the objects
		
		// Update the renderer
		myRenderer.Update(dt);
	}

	// Delete objects here

	// Remember to shutdown the solver
	mySolver.Shutdown();

	// Remember to shutdown renderer
	myRenderer.Shutdown();

	return 0;
}
