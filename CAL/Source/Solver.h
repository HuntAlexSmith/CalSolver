//*****************************************************************************
//	Filename: Solver.h
//  Author:	  Hunter Smith
//  Date:	  08/14/2022
//  Description:
//		Class for handling all the solving stuff
//*****************************************************************************
#pragma once

#include "Object.h"
#include "Renderer.h"

#define WIDTH 7
#define HEIGHT 8

class Solver {
public:

	enum Month {
		MonthInvalid = -1,
		JAN,
		FEB,
		MAR,
		APR,
		MAY,
		JUN,
		JUL,
		AUG,
		SEP,
		OCT,
		NOV,
		DEC
	};

	enum DayOfWeek {
		DayInvalid = -1,
		MON,
		TUE,
		WED,
		THU,
		FRI,
		SAT,
		SUN
	};

	// Constructor and Destructor
	Solver();
	~Solver();

	// Member functions
	void Initialize();
	void Shutdown();

	void Reset();

	bool Solve(Month month, unsigned int day, DayOfWeek dayOfWeek);

	Object** GetBoard();
	int GetBoardCount();

	Object** GetPieces();
	int GetPieceCount();

	Object** GetPlacedPieces();
	int GetPlacedPieceCount();

	void SetRenderer(Renderer* renderer);

private:

	bool SolveRec();

	void PlacePiece(int xPos, int yPos);
	void RemovePiece();

	void RenderPlaced();

	std::vector<Texture*> textures_;

	std::vector<Object*> tiles_;
	std::vector<Object*> pieces_;
	std::vector<Object*> placed_;

	int board_[WIDTH][HEIGHT];
	int boardMax_;

	int recDepth_;

	Renderer* renderer_;

};
