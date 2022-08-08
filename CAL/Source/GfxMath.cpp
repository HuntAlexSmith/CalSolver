//*****************************************************************************
//	Filename: GfxMath.cpp
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This will handle any graphics math functions that need to be handled,
//		as well as maybe abstract some of what glm does
//*****************************************************************************

#include "GfxMath.h"

glm::vec3 GfxMath::Point2D(float x, float y)
{
	return glm::vec3(x, y, 1.0f);
}

glm::vec3 GfxMath::Vector2D(float x, float y)
{
	return glm::vec3(x, y, 0.0f);
}
