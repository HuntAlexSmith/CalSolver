//*****************************************************************************
//	Filename: Stub.h
//  Author:	  YOUR NAME HERE
//  Date:	  THE DATE HERE
//  Description:
//		WRITE DESCRIPTION OF FILE HERE
//*****************************************************************************
#pragma once

#include "glad/glad.h"
#include <string>

class Texture {
public:
	// Constructor and destructor
	Texture(std::string name, const char* texPath);
	~Texture();

	const std::string Name();
	const GLuint TexGL();

private:

	std::string name_;
	GLuint texture_;

};
