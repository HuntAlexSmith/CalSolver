//*****************************************************************************
//	Filename: Camera.h
//  Author:	  Hunter Smith
//  Date:	  08/11/2022
//  Description:
//		Camera class, which will simulate a camera for rendering
//*****************************************************************************

#include "Camera.h"

Camera::Camera(float h, float a, glm::vec4 center) :
	aspect_(a)
	, width_(a*h)
	, height_(h)
	, rightVec_(GfxMath::Vector2D(1, 0))
	, upVec_(GfxMath::Vector2D(0, 1))
	, center_(center)
	, worldToCam_(glm::mat4(1))
	, camToWorld_(glm::mat4(1))
	, camToNDC_(glm::mat4(1))
	, isDirty_(false)
{
	CalcMats();
}

Camera::~Camera()
{

}

const glm::mat4 Camera::WorldToCam()
{
	if (isDirty_) {
		CalcMats();
		isDirty_ = false;
	}
	return worldToCam_;
}

const glm::mat4 Camera::CamToWorld()
{
	if (isDirty_) {
		CalcMats();
		isDirty_ = false;
	}
	return camToWorld_;
}

const glm::mat4 Camera::CamToNDC()
{
	if (isDirty_) {
		CalcMats();
		isDirty_ = false;
	}
	return camToNDC_;
}

void Camera::CalcMats()
{
	// Calculate the camera to world matrix
	camToWorld_ = glm::mat4(
		rightVec_.x, rightVec_.y, 0, 0,
		upVec_.x, upVec_.y, 0, 0,
		0, 0, 1, 0,
		center_.x, center_.y, 0, 1
	);

	// Calculate the world to camera matrix
	worldToCam_ = GfxMath::AffineInverse(camToWorld_);

	// Calculate cam to NDC matrix
	camToNDC_ = glm::mat4(1);
	camToNDC_[0][0] = 2.0f / width_;
	camToNDC_[1][1] = 2.0f / height_;
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
