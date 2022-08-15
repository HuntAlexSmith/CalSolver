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
}

void Solver::Shutdown()
{
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
	return nullptr;
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
