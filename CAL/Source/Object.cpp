//*****************************************************************************
//	Filename: Object.cpp
//  Author:	  Hunter Smith
//  Date:	  08/12/2022
//  Description:
//		Object for rendering the puzzle pieces. Not trying to make this very
//		open ended, so can code this to however is needed easily
//*****************************************************************************

#include "Object.h"
#include <cmath>

// Constructor and Destructor
Object::Object() : 
	positions_()
	, worldPos_(GfxMath::Point2D(0, 0))
	, tint_(glm::vec3(0))
	, alpha_(1.0f)
	, texture_(nullptr)
	, curRot_(0)
{
}

Object::~Object()
{
}

// Member functions
const glm::vec4* Object::GetPos()
{
	if (positions_.size() > 0)
		return &positions_[0];
	return nullptr;
}

const glm::vec4 Object::GetWorldPos()
{
	return worldPos_;
}

const int Object::GetPosCount()
{
	return positions_.size();
}

const glm::vec3 Object::GetTint()
{
	return tint_;
}

const float Object::GetAlpha()
{
	return alpha_;
}

void Object::AddPosition(glm::vec4 pos)
{
	positions_.push_back(pos);
}

void Object::SetWorldPos(glm::vec4 worldPos)
{
	worldPos_ = worldPos;
}

void Object::SetTint(glm::vec3 tint)
{
	tint_ = tint;
}
void Object::SetAlpha(float alpha)
{
	alpha_ = alpha;
}

Texture* Object::GetTexture()
{
	return texture_;
}

void Object::SetTexture(Texture* tex)
{
	texture_ = tex;
}

void Object::Rotate90()
{
	// Generate a rotation matrix
	float rad90 = glm::radians(90.0f);
	glm::mat4 rotMat(1);
	rotMat[0][0] = cosf(rad90);
	rotMat[0][1] = sinf(rad90);
	rotMat[1][0] = -sinf(rad90);
	rotMat[1][1] = cosf(rad90);

	// Iterate over all positions and rotate them
	int posCount = positions_.size();
	for (int i = 0; i < posCount; ++i) {
		glm::vec4 newPos = rotMat * positions_[i];
		newPos.x = round(newPos.x);
		newPos.y = round(newPos.y);
		positions_[i] = newPos;
	}

	// Increment current rotation
	curRot_ += 90;
	if (curRot_ >= 360) {
		curRot_ = 0;
	}
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
