//*****************************************************************************
//	Filename: GfxMath.h
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This will handle any graphics math functions that need to be handled,
//		as well as maybe abstract some of what glm does
//*****************************************************************************
#pragma once

#include "glm/glm.hpp"

namespace GfxMath {

	glm::vec4 Point2D(float x, float y);

	glm::vec4 Vector2D(float x, float y);

	glm::mat4 AffineInverse(const glm::mat4& affine);
};