//*****************************************************************************
//	Filename: Solver.cpp
//  Author:	  Hunter Smith
//  Date:	  08/14/2022
//  Description:
//		Class for handling all the solving stuff
//*****************************************************************************

#include "Solver.h"
#include "glm/glm.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <exception>

static glm::ivec2 invalidPositions[6] = {
	glm::ivec2(0, 0),
	glm::ivec2(1, 0),
	glm::ivec2(2, 0),
	glm::ivec2(3 ,0),
	glm::ivec2(6, 6),
	glm::ivec2(6, 7)
};

Solver::Solver() :
	tiles_()
	, pieces_()
	, placed_()
	, board_{0}
	, boardMax_(WIDTH*HEIGHT)
	, recDepth_(0)
	, renderer_(nullptr)
{
}

Solver::~Solver()
{

}

// Member functions
void Solver::Initialize()
{
	// Initialize the board
	for (int i = 0; i < 6; ++i) {
		board_[invalidPositions[i].x][invalidPositions[i].y] = -1;
	}

	// Load all the month textures
	textures_.push_back(new Texture("Tile Jan", "Assets/Done/Tile_Jan.png"));
	textures_.push_back(new Texture("Tile Feb", "Assets/Done/Tile_Feb.png"));
	textures_.push_back(new Texture("Tile Mar", "Assets/Done/Tile_Mar.png"));
	textures_.push_back(new Texture("Tile Apr", "Assets/Done/Tile_Apr.png"));
	textures_.push_back(new Texture("Tile May", "Assets/Done/Tile_May.png"));
	textures_.push_back(new Texture("Tile Jun", "Assets/Done/Tile_Jun.png"));
	textures_.push_back(new Texture("Tile Jul", "Assets/Done/Tile_Jul.png"));
	textures_.push_back(new Texture("Tile Aug", "Assets/Done/Tile_Aug.png"));
	textures_.push_back(new Texture("Tile Sep", "Assets/Done/Tile_Sep.png"));
	textures_.push_back(new Texture("Tile Oct", "Assets/Done/Tile_Oct.png"));
	textures_.push_back(new Texture("Tile Nov", "Assets/Done/Tile_Nov.png"));
	textures_.push_back(new Texture("Tile Dec", "Assets/Done/Tile_Dec.png"));

	// Load all necessary textures
	for (int i = 1; i < 32; ++i) {
		std::string filePath = "Assets/Done/Tile_";
		filePath += std::to_string(i);
		filePath += ".png";
		Texture* newTex = new Texture("Tile " + i, filePath.c_str());
		textures_.push_back(newTex);
	}

	// Load all the day textures
	textures_.push_back(new Texture("Tile Sun", "Assets/Done/Tile_Sun.png"));
	textures_.push_back(new Texture("Tile Mon", "Assets/Done/Tile_Mon.png"));
	textures_.push_back(new Texture("Tile Tue", "Assets/Done/Tile_Tue.png"));
	textures_.push_back(new Texture("Tile Wed", "Assets/Done/Tile_Wed.png"));
	textures_.push_back(new Texture("Tile Thu", "Assets/Done/Tile_Thu.png"));
	textures_.push_back(new Texture("Tile Fri", "Assets/Done/Tile_Fri.png"));
	textures_.push_back(new Texture("Tile Sat", "Assets/Done/Tile_Sat.png"));

	// Now generate all the tile objects
	int curTex = 0;

	// Set all the textures
	for (int j = HEIGHT - 1; j >= 0; --j) {
		for (int i = 0; i < WIDTH; ++i) {
			if (board_[i][j] > -1) {
				Object* newObj = new Object();
				newObj->AddPosition(GfxMath::Point2D(i, j));
				newObj->SetTexture(textures_[curTex]);
				curTex++;
				tiles_.push_back(newObj);
			}
		}
	}

	// Create the objects and give them their needed shape

	// The colors we will use
	glm::vec3 red(1, 0, 0);
	glm::vec3 green(0, 1, 0);
	glm::vec3 blue(0, 0, 1);
	glm::vec3 yellow(1, 1, 0);
	glm::vec3 cyan(0, 1, 1);
	glm::vec3 magenta(1, 0, 1);
	glm::vec3 color1(0.2f, 0.5f, 0.8f);
	glm::vec3 color2(0.8f, 0.5f, 0.2f);
	glm::vec3 color3(0.5f, 0.2f, 0.8f);
	glm::vec3 color4(0.8f, 0.2f, 0.5f);

	// **
	//** 
	Object* smallS = new Object();
	smallS->AddPosition(GfxMath::Point2D(0, 0));
	smallS->AddPosition(GfxMath::Point2D(1, 0));
	smallS->AddPosition(GfxMath::Point2D(1, 1));
	smallS->AddPosition(GfxMath::Point2D(2, 1));
	smallS->SetTint(red);
	smallS->SetWorldPos(GfxMath::Point2D(-10, 8));
	smallS->SetID(1);

	//  *
	//***
	Object* smallL = new Object();
	smallL->AddPosition(GfxMath::Point2D(0, 0));
	smallL->AddPosition(GfxMath::Point2D(1, 0));
	smallL->AddPosition(GfxMath::Point2D(2, 0));
	smallL->AddPosition(GfxMath::Point2D(2, 1));
	smallL->SetTint(green);
	smallL->SetWorldPos(GfxMath::Point2D(-10, 5));
	smallL->SetID(2);

	//****
	Object* iPiece = new Object();
	iPiece->AddPosition(GfxMath::Point2D(0, 0));
	iPiece->AddPosition(GfxMath::Point2D(1, 0));
	iPiece->AddPosition(GfxMath::Point2D(2, 0));
	iPiece->AddPosition(GfxMath::Point2D(3, 0));
	iPiece->SetTint(blue);
	iPiece->SetWorldPos(GfxMath::Point2D(-10, 2));
	iPiece->SetID(3);

	// **
	//***
	Object* block = new Object();
	block->AddPosition(GfxMath::Point2D(0, 0));
	block->AddPosition(GfxMath::Point2D(1, 0));
	block->AddPosition(GfxMath::Point2D(1, 1));
	block->AddPosition(GfxMath::Point2D(2, 0));
	block->AddPosition(GfxMath::Point2D(2, 1));
	block->SetTint(yellow);
	block->SetWorldPos(GfxMath::Point2D(-10, -1));
	block->SetID(4);

	//   *
	//****
	Object* longL = new Object();
	longL->AddPosition(GfxMath::Point2D(0, 0));
	longL->AddPosition(GfxMath::Point2D(1, 0));
	longL->AddPosition(GfxMath::Point2D(2, 0));
	longL->AddPosition(GfxMath::Point2D(3, 0));
	longL->AddPosition(GfxMath::Point2D(3, 1));
	longL->SetTint(cyan);
	longL->SetWorldPos(GfxMath::Point2D(-10, -4));
	longL->SetID(5);

	//***
	//* *
	Object* arch = new Object();
	arch->AddPosition(GfxMath::Point2D(0, 0));
	arch->AddPosition(GfxMath::Point2D(0, 1));
	arch->AddPosition(GfxMath::Point2D(1, 1));
	arch->AddPosition(GfxMath::Point2D(2, 1));
	arch->AddPosition(GfxMath::Point2D(2, 0));
	arch->SetTint(magenta);
	arch->SetWorldPos(GfxMath::Point2D(-5, 8));
	arch->SetID(6);

	// ***
	//**
	Object* funky = new Object();
	funky->AddPosition(GfxMath::Point2D(0, 0));
	funky->AddPosition(GfxMath::Point2D(1, 0));
	funky->AddPosition(GfxMath::Point2D(1, 1));
	funky->AddPosition(GfxMath::Point2D(2, 1));
	funky->AddPosition(GfxMath::Point2D(3, 1));
	funky->SetTint(color1);
	funky->SetWorldPos(GfxMath::Point2D(-5, 5));
	funky->SetID(7);

	//  *
	//***
	//*
	Object* bigS = new Object();
	bigS->AddPosition(GfxMath::Point2D(0, 0));
	bigS->AddPosition(GfxMath::Point2D(0, 1));
	bigS->AddPosition(GfxMath::Point2D(1, 1));
	bigS->AddPosition(GfxMath::Point2D(2, 1));
	bigS->AddPosition(GfxMath::Point2D(2, 2));
	bigS->SetTint(color2);
	bigS->SetWorldPos(GfxMath::Point2D(-5, 1));
	bigS->SetID(8);

	// *
	// *
	//***
	Object* tPiece = new Object();
	tPiece->AddPosition(GfxMath::Point2D(0, 0));
	tPiece->AddPosition(GfxMath::Point2D(1, 0));
	tPiece->AddPosition(GfxMath::Point2D(2, 0));
	tPiece->AddPosition(GfxMath::Point2D(1, 1));
	tPiece->AddPosition(GfxMath::Point2D(1, 2));
	tPiece->SetTint(color3);
	tPiece->SetWorldPos(GfxMath::Point2D(-5, -3));
	tPiece->SetID(9);

	//  *
	//  *
	//***
	Object* corner = new Object();
	corner->AddPosition(GfxMath::Point2D(0, 0));
	corner->AddPosition(GfxMath::Point2D(1, 0));
	corner->AddPosition(GfxMath::Point2D(2, 0));
	corner->AddPosition(GfxMath::Point2D(2, 1));
	corner->AddPosition(GfxMath::Point2D(2, 2));
	corner->SetTint(color4);
	corner->SetWorldPos(GfxMath::Point2D(-5, -7));
	corner->SetID(10);

	// Now add all the pieces to the vector
	pieces_.push_back(smallS);
	pieces_.push_back(smallL);
	pieces_.push_back(iPiece);
	pieces_.push_back(block);
	pieces_.push_back(longL);
	pieces_.push_back(arch);
	pieces_.push_back(funky);
	pieces_.push_back(bigS);
	pieces_.push_back(tPiece);
	pieces_.push_back(corner);

	/*
	std::random_device rd;
	auto rng = std::default_random_engine(rd());
	std::shuffle(std::begin(pieces_), std::end(pieces_), rng);
	*/
}

void Solver::Shutdown()
{
	// Delete all the objects
	for (Object* obj : pieces_) {
		delete obj;
	}
	pieces_.clear();

	for (Object* obj : placed_) {
		delete obj;
	}
	placed_.clear();

	// Make sure to delete everything
	int objCount = tiles_.size();
	for (int i = 0; i < objCount; ++i) {
		delete tiles_[i];
	}
	tiles_.clear();

	int texCount = textures_.size();
	for (int i = 0; i < texCount; ++i) {
		delete textures_[i];
	}
	textures_.clear();
}

void Solver::Reset()
{
	// Initialize the board
	for (int i = 0; i < 6; ++i) {
		board_[invalidPositions[i].x][invalidPositions[i].y] = -1;
	}

	// Make sure all pieces in placed are in pieces
	while (!placed_.empty()) {
		pieces_.push_back(placed_.back());
		placed_.pop_back();
	}

	// Now make sure all orientations are reset
	for (Object* obj : pieces_) {
		// If object is mirrored, un-mirror it
		if (obj->IsMirrored())
			obj->Mirror();

		// Rotate object back to original
		while (obj->GetRot() > 0) {
			obj->Rotate90();
		}

		// Set position to origin
		obj->SetWorldPos(GfxMath::Point2D(0, 0));
	}

	// Reset the rec depth
	recDepth_ = 0;
}

bool Solver::Solve(Month month, unsigned int day, DayOfWeek dayOfWeek)
{
	// Reset the board
	Reset();

	// Validate Month parameter
	if (month > Month::DEC || month <= Month::MonthInvalid) {
		std::cout << "Month Invalid, Can't Solve" << std::endl;
		return false;
	}

	// Validate Day of Week parameter
	if (dayOfWeek > DayOfWeek::SUN || dayOfWeek <= DayOfWeek::DayInvalid) {
		std::cout << "Day of Week Invalid, Can't Solve" << std::endl;
	}

	// Validate Day
	if (day == 0) {
		std::cout << "Day Can't Be Zero!" << std::endl;
		return false;
	}

	// Validate that day exists within month
	if (month == Month::FEB) {

		if (day > 29) {
			std::cout << "Day Invalid" << std::endl;
			return false;
		}
	}

	else if (month % 2 == 1) {
		if (day > 30) {
			std::cout << "Day Invalid" << std::endl;
			return false;
		}
	}

	else {
		if (day > 31) {
			std::cout << "Day Invalid" << std::endl;
			return false;
		}
	}

	// Set the month space as invalid
	int xPos = month % 6;
	int yPos = (HEIGHT-1) - (month / 6);
	board_[xPos][yPos] = -1;

	// Set the day space as invalid
	xPos = (day - 1) % 7;
	yPos = (HEIGHT-3) - ((day - 1) / 7);
	board_[xPos][yPos] = -1;

	// Set the day of the week position
	switch (dayOfWeek) {
		case SUN:
			board_[3][1] = -1;
			break;
		case MON:
			board_[4][1] = -1;
			break;
		case TUE:
			board_[5][1] = -1;
			break;
		case WED:
			board_[6][1] = -1;
			break;
		case THU:
			board_[4][0] = -1;
			break;
		case FRI:
			board_[5][0] = -1;
			break;
		case SAT:
			board_[6][0] = -1;
			break;
	}

	// Now we are ready to attempt solving
	bool result = SolveRec();
	std::cout << "Done" << std::endl;
	return result;
}

Object** Solver::GetBoard()
{
	if (tiles_.size() > 0)
		return &tiles_[0];
	return nullptr;
}

int Solver::GetBoardCount()
{
	return tiles_.size();
}

Object** Solver::GetPieces()
{
	if (pieces_.size() > 0) {
		return &pieces_[0];
	}
	return nullptr;
}

int Solver::GetPieceCount()
{
	return pieces_.size();
}

Object** Solver::GetPlacedPieces()
{
	if (placed_.size() > 0) {
		return &placed_[0];
	}
	return nullptr;
}

int Solver::GetPlacedPieceCount()
{
	return placed_.size();
}

bool Solver::SolveRec()
{
	// Increment recursion
	++recDepth_;

	/*
	if (recDepth_ == 10000) {
		RenderPlaced();
		recDepth_ = 0;
	}
	*/

	// End check for recursion
	if (pieces_.empty())
		return true;

	// Get the current piece to attempt to place
	Object* curPiece = pieces_.back();

	// First check for mirror or not
	for (int m = 0; m < 2; ++m) {

		// Now check for rotation
		for (int r = 0; r < 4; ++r) {

			// Check every position on the board
			for (int pos = 0; pos < boardMax_; ++pos) {
				// Calculate where the position actually is
				int xPos = pos % WIDTH;
				int yPos = pos / WIDTH;

				// Get the cur Piece positions
				const glm::vec4* objPositions = curPiece->GetPos();
				int posCount = curPiece->GetPosCount();

				// Valid flag
				bool valid = true;

				// Iterate over piece positions
				for (int i = 0; i < posCount; ++i) {
					// Get the current position and offsets
					glm::vec4 curPos = objPositions[i];
					int xOff = static_cast<int>(curPos.x);
					int yOff = static_cast<int>(curPos.y);

					// Check if anything is invalid
					if (xPos + xOff >= WIDTH ||
						xPos + xOff < 0 ||
						yPos + yOff >= HEIGHT ||
						yPos + yOff < 0)
					{
						valid = false;
						break;
					}

					else if (board_[xPos + xOff][yPos + yOff] != 0) {
						valid = false;
						break;
					}
				}

				// If piece is valid, place it and call recursion
				if (valid) {
					// Place Piece
					PlacePiece(xPos, yPos);

					// Check if the piece placement was valid
					if (CheckForIsland()) {
						RemovePiece();
						continue;
					}

					// Render the current pieces
					// RenderPlaced();

					// Call Recursion
					if (SolveRec())
						return true;

					// Remove Piece
					RemovePiece();
				}

			}

			// Remember to rotate for next go around
			curPiece->Rotate90();
		}

		// Remember to mirror for next go around
		curPiece->Mirror();
	}

	return false;
}

void Solver::PlacePiece(int xPos, int yPos)
{
	// Get back piece from available pieces
	Object* pieceToPlace = pieces_.back();
	pieces_.pop_back();

	// Set position for rendering
	pieceToPlace->SetWorldPos(GfxMath::Point2D(xPos, yPos));

	// Get positions and position count
	const glm::vec4* piecePos = pieceToPlace->GetPos();
	int posCount = pieceToPlace->GetPosCount();
	for (int i = 0; i < posCount; ++i) {
		// Get current position and offsets
		glm::vec4 curPos = piecePos[i];
		int xOff = static_cast<int>(curPos.x);
		int yOff = static_cast<int>(curPos.y);

		// Set that value with the piece ID
		board_[xPos + xOff][yPos + yOff] = pieceToPlace->GetID();
	}

	// Add the piece to the placed array
	placed_.push_back(pieceToPlace);
}

void Solver::RemovePiece()
{
	// Get the piece from the placed vector to remove
	Object* pieceToRemove = placed_.back();
	placed_.pop_back();

	// Get current piece info and reset the board
	const glm::vec4* piecePos = pieceToRemove->GetPos();
	int posCount = pieceToRemove->GetPosCount();
	glm::vec4 curWorldPos = pieceToRemove->GetWorldPos();
	int xPos = static_cast<int>(curWorldPos.x);
	int yPos = static_cast<int>(curWorldPos.y);
	for (int i = 0; i < posCount; ++i) {
		// Get current position and offsets
		glm::vec4 curPos = piecePos[i];
		int xOff = static_cast<int>(curPos.x);
		int yOff = static_cast<int>(curPos.y);

		// Set that value with the piece ID
		board_[xPos + xOff][yPos + yOff] = 0;
	}

	// Add the piece to the available pieces
	pieces_.push_back(pieceToRemove);
}

void Solver::SetRenderer(Renderer* renderer)
{
	renderer_ = renderer;
}

void Solver::RenderPlaced()
{
	for (Object* obj : tiles_) {
		renderer_->Render(obj);
	}
	for (Object* obj : placed_) {
		renderer_->Render(obj);
	}
	renderer_->Update(0.0f);
}

bool Solver::CheckForIsland()
{
	for (int i = 0; i < boardMax_; ++i) {
		// Calculate x and y positions
		int xPos = i % WIDTH;
		int yPos = i / WIDTH;

		// First check if this space should be filled or not
		if (board_[xPos][yPos] != 0)
			continue;
			
		// Keep an array of the values nearby
		int vals[4] = { -1 };

		// Check Up
		if (yPos + 1 < 0 || yPos + 1 >= HEIGHT)
			vals[0] = -1;
		else
			vals[0] = board_[xPos][yPos+1];

		// Check Right
		if (xPos + 1 < 0 || xPos + 1 >= WIDTH)
			vals[1] = -1;
		else
			vals[1] = board_[xPos+1][yPos];

		// Check Down
		if (yPos - 1 < 0 || yPos - 1 >= HEIGHT)
			vals[2] = -1;
		else
			vals[2] = board_[xPos][yPos-1];

		// Check Left
		if (xPos - 1 < 0 || xPos - 1 >= WIDTH)
			vals[3] = -1;
		else
			vals[3] = board_[xPos-1][yPos];

		// Iterate over and see if this is an island
		bool isIsland = true;
		for (int j = 0; j < 4; ++j) {
			if (vals[j] == 0)
				isIsland = false;
		}
		if (isIsland)
			return true;
	}
	return false;
}

//*****************************************************************************
//	Description
//		WRITE DESCRIPTION OF FUNCTION HERE
// 
//	Param MY_PARAM
//		WRITE WHAT PARAMETER DOES
// 
//	Return
//		SAY WHAT THE FUNCTION RETURNS IF NECESSARY
//*****************************************************************************
