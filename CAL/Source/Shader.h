//*****************************************************************************
//	Filename: Shader.cpp
//  Author:	  Hunter Smith
//  Date:	  08/08/2022
//  Description:
//		Wrapper for OpenGL Shaders
//*****************************************************************************
#pragma once

#include <string>
#include <map>
#include "glad/glad.h"

class Shader {
public:

	// Constructor and destructor
	Shader(const char* vertFilePath, const char* fragFilePath);
	~Shader();

	// Member functions
	void Use();

	GLint GetAttribLocation(std::string attribName);
	GLint GetUniformLocation(std::string uniformName);

	bool Failed();

private:

	std::string ReadFile(const char* filepath);

	// OpenGL program
	GLuint program_;

	// Attribute and Uniform locations
	std::map<std::string, GLint> attribs_;
	std::map<std::string, GLint> uniforms_;

	// Failed check
	bool failed_;

};
