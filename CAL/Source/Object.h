//*****************************************************************************
//	Filename: Object.cpp
//  Author:	  Hunter Smith
//  Date:	  08/12/2022
//  Description:
//		Object for rendering the puzzle pieces. Not trying to make this very
//		open ended, so can code this to however is needed easily
//*****************************************************************************
#pragma once

#include "GfxMath.h"
#include "Texture.h"
#include <vector>

class Object {
public:
	// Constructor and Destructor
	Object();
	~Object();

	// Member functions
	const glm::vec4* GetPos();
	const int GetPosCount();
	const glm::vec3 GetTint();
	const float GetAlpha();
	Texture* GetTexture();

	void AddPosition(glm::vec4 pos);
	void SetTint(glm::vec3 tint);
	void SetAlpha(float alpha);
	void SetTexture(Texture* tex);

private:

	std::vector<glm::vec4> positions_;
	glm::vec3 tint_;
	float alpha_;
	Texture* texture_;

};
