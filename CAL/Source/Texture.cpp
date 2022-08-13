//*****************************************************************************
//	Filename: Texture.cpp
//  Author:	  Hunter Smith
//  Date:	  08/13/2022
//  Description:
//		Wrapper class for handling OpenGL textures
//*****************************************************************************

#include "Texture.h"
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(std::string name, const char* texPath) :
	name_(name)
	, texture_(0)
{
	// Load the texture using stb_image
	int width, height, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texPath, &width, &height, &numColCh, 0);
	if (!data) {
		std::cout << "Texture failed to load" << std::endl;
		return;
	}

	// Generate the OpenGL texture
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	// Set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Load the actual texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Remember to delete the old data
	stbi_image_free(data);

	// Remember to unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture_);
}

const std::string Texture::Name()
{
	return name_;
}

const GLuint Texture::TexGL()
{
	return texture_;
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
