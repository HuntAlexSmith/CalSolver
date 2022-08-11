//*****************************************************************************
//	Filename: Camera.h
//  Author:	  Hunter Smith
//  Date:	  08/11/2022
//  Description:
//		Camera class, which will simulate a camera for rendering
//*****************************************************************************
#pragma once

#include "GfxMath.h"

class Camera {
public:
	// Constructor and destructor
	Camera(float h, float a, glm::vec4 center);
	~Camera();

	// Member Functions
	const glm::mat4 WorldToCam();
	const glm::mat4 CamToWorld();
	const glm::mat4 CamToNDC();

private:

	// Private function for calculating the matrices
	void CalcMats();

	// Camera Data
	float aspect_;
	float width_;
	float height_;

	glm::vec4 rightVec_;
	glm::vec4 upVec_;
	glm::vec4 center_;

	// Transformations
	glm::mat4 worldToCam_;
	glm::mat4 camToWorld_;
	glm::mat4 camToNDC_;

	// Dirty flag
	bool isDirty_;

};
