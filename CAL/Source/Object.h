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
	const glm::vec4 GetWorldPos();
	const int GetPosCount();
	const glm::vec3 GetTint();
	const float GetAlpha();
	Texture* GetTexture();

	void AddPosition(glm::vec4 pos);
	void SetWorldPos(glm::vec4 worldPos);
	void SetTint(glm::vec3 tint);
	void SetAlpha(float alpha);
	void SetTexture(Texture* tex);

	void Rotate90();

private:

	// The full positioning of the piece
	std::vector<glm::vec4> positions_;

	// World position of the origin
	glm::vec4 worldPos_;

	// Other rendering necessitites
	glm::vec3 tint_;
	float alpha_;
	Texture* texture_;

	// Current rotation
	int curRot_;

};
