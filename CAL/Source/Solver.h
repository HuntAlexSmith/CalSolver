//*****************************************************************************
//	Filename: Solver.h
//  Author:	  Hunter Smith
//  Date:	  08/14/2022
//  Description:
//		Class for handling all the solving stuff
//*****************************************************************************
#pragma once

#include "Object.h"

#define WIDTH 7
#define HEIGHT 8

class Solver {
public:

	// Constructor and Destructor
	Solver();
	~Solver();

	// Member functions
	void Initialize();
	void Shutdown();

	Object** GetBoard();
	int GetBoardCount();

	Object** GetPieces();

private:

	std::vector<Texture*> textures_;

	std::vector<Object*> tiles_;
	std::vector<Object*> pieces_;

	int board_[WIDTH][HEIGHT];

};
