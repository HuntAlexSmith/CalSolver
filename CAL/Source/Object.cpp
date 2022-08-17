//*****************************************************************************
//	Filename: Object.cpp
//  Author:	  Hunter Smith
//  Date:	  08/12/2022
//  Description:
//		Object for rendering the puzzle pieces. Not trying to make this very
//		open ended, so can code this to however is needed easily
//*****************************************************************************

#include "Object.h"

// Constructor and Destructor
Object::Object() : 
	positions_()
	, worldPos_(GfxMath::Point2D(0, 0))
	, tint_(glm::vec3(0))
	, alpha_(1.0f)
	, texture_(nullptr)
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
