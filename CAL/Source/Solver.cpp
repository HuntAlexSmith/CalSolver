//*****************************************************************************
//	Filename: Solver.cpp
//  Author:	  Hunter Smith
//  Date:	  08/14/2022
//  Description:
//		Class for handling all the solving stuff
//*****************************************************************************

#include "Solver.h"
#include "glm/glm.hpp"

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
	, board_{0}
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

	//  *
	//***
	Object* smallL = new Object();
	smallL->AddPosition(GfxMath::Point2D(0, 0));
	smallL->AddPosition(GfxMath::Point2D(1, 0));
	smallL->AddPosition(GfxMath::Point2D(2, 0));
	smallL->AddPosition(GfxMath::Point2D(2, 1));
	smallL->SetTint(green);
	smallL->SetWorldPos(GfxMath::Point2D(-10, 5));

	//****
	Object* iPiece = new Object();
	iPiece->AddPosition(GfxMath::Point2D(0, 0));
	iPiece->AddPosition(GfxMath::Point2D(1, 0));
	iPiece->AddPosition(GfxMath::Point2D(2, 0));
	iPiece->AddPosition(GfxMath::Point2D(3, 0));
	iPiece->SetTint(blue);
	iPiece->SetWorldPos(GfxMath::Point2D(-10, 2));

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
}

void Solver::Shutdown()
{
	// Delete all the objects
	for (Object* obj : pieces_) {
		delete obj;
	}
	pieces_.clear();

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
