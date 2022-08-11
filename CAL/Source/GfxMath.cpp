//*****************************************************************************
//	Filename: GfxMath.cpp
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This will handle any graphics math functions that need to be handled,
//		as well as maybe abstract some of what glm does
//*****************************************************************************

#include "GfxMath.h"

glm::vec4 GfxMath::Point2D(float x, float y)
{
	return glm::vec4(x, y, 0.0f, 1.0f);
}

glm::vec4 GfxMath::Vector2D(float x, float y)
{
	return glm::vec4(x, y, 0.0f, 0.0f);
}

glm::mat4 GfxMath::AffineInverse(const glm::mat4& affine)
{
	// Calculate the inverse of the linear part
	glm::mat4 linearInvTrans = glm::mat4(
		glm::inverse(
			glm::mat3(affine)
		)
	);

	// Calculate the inverse of the translation part
	glm::mat4 invTrans = glm::mat4(1);
	invTrans[3][0] = -affine[3][0];
	invTrans[3][1] = -affine[3][1];
	invTrans[3][2] = -affine[3][2];

	// Multiply and return
	return linearInvTrans * invTrans;
}
