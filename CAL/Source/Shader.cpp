//*****************************************************************************
//	Filename: Shader.cpp
//  Author:	  Hunter Smith
//  Date:	  08/08/2022
//  Description:
//		Wrapper for OpenGL Shaders
//*****************************************************************************

#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

Shader::Shader(const char* vertFilePath, const char* fragFilePath) : program_(0)
	, attribs_()
	, uniforms_()
	, failed_(false)
{
	// Read in vertex shader code
	std::string vertCodeStr = ReadFile(vertFilePath);
	if (vertCodeStr.empty()) {
		std::cout << "Shader failed to be created, could not read Vertex Shader File" << std::endl;
		failed_ = true;
		return;
	}
	const char* vertCode = vertCodeStr.c_str();

	// Create vertex shader, give it code, and compile it
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertCode, nullptr);
	glCompileShader(vertexShader);

	// Check for error
	GLint worked = 1;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &worked);
	if (!worked) {
		std::string errMsg = "Vert Shader failed to compile:\n";
		char errBuff[1024];
		glGetShaderInfoLog(vertexShader, 1024, 0, errBuff);
		errMsg += errBuff;
		std::cout << errMsg << std::endl;
		failed_ = true;
		return;
	}

	// Read in fragment shader code
	std::string fragCodeStr = ReadFile(fragFilePath);
	if (fragCodeStr.empty()){
		std::cout << "Shader failed to be created, could not read Frag Shader File" << std::endl;
		failed_ = true;
		return;
	}
	const char* fragCode = fragCodeStr.c_str();

	// Create fragment shader, give it code, and compile
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCode, nullptr);
	glCompileShader(fragShader);

	// Error check 
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &worked);
	if (!worked)
	{
		std::string errMsg = "Fragment Shader failed to compile:\n";
		char errBuff[1024];
		glGetShaderInfoLog(fragShader, 1024, 0, errBuff);
		errMsg += errBuff;
		std::cout << errMsg << std::endl;
		glDeleteShader(vertexShader);
		failed_ = true;
		return;
	}

	// Now make the actual program
	program_ = glCreateProgram();
	glAttachShader(program_, fragShader);
	glAttachShader(program_, vertexShader);
	glLinkProgram(program_);

	// Don't need the shaders anymore
	glDeleteShader(fragShader);
	glDeleteShader(vertexShader);

	// Error check for link
	glGetProgramiv(program_, GL_LINK_STATUS, &worked);
	if (!worked)
	{
		std::string errMsg = "Fragment Shader failed to compile:\n";
		char errBuff[1024];
		glGetProgramInfoLog(program_, 1024, 0, errBuff);
		errMsg += errBuff;
		glDeleteProgram(program_);
		std::cout << errMsg << std::endl;
		failed_ = true;
		return;
	}

	// Get all attribs in the program
	GLint attribCount;
	glGetProgramiv(program_, GL_ACTIVE_ATTRIBUTES, &attribCount);

	GLint size;
	GLenum type;
	const GLsizei bufSize = 16;
	GLchar varName[bufSize];
	GLsizei length;

	for (GLint i = 0; i < attribCount; ++i)
	{
		glGetActiveAttrib(program_, i, bufSize, &length, &size, &type, varName);
		std::pair<std::string, GLint> attribToAdd(std::string(varName), glGetAttribLocation(program_, varName));
		attribs_.insert(attribToAdd);
	}

	// Get all the uniforms in the program
	GLint uniformCount;
	glGetProgramiv(program_, GL_ACTIVE_UNIFORMS, &uniformCount);

	for (GLint i = 0; i < uniformCount; ++i)
	{
		glGetActiveUniform(program_, i, bufSize, &length, &size, &type, varName);
		std::pair<std::string, GLint> uniformToAdd(std::string(varName), glGetUniformLocation(program_, varName));
		uniforms_.insert(uniformToAdd);
	}
}

Shader::~Shader()
{
	if(uniforms_.size())
		uniforms_.clear();

	if(attribs_.size())
		attribs_.clear();

	glUseProgram(0);
	glDeleteProgram(program_);
}

// Member functions
void Shader::Use()
{
	glUseProgram(program_);
}

GLint Shader::GetAttribLocation(std::string attribName)
{
	auto result = attribs_.find(attribName);
	if (result == attribs_.end())
		return -1;
	return result->second;
}

GLint Shader::GetUniformLocation(std::string uniformName)
{
	auto result = uniforms_.find(uniformName);
	if (result == uniforms_.end())
		return -1;
	return result->second;
}

std::string Shader::ReadFile(const char* filepath)
{
	std::ifstream file;
	std::stringstream contents;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// Open the file
		file.open(filepath);

		// Dump the contents into buffer
		contents << file.rdbuf();

		// Close the file
		file.close();
	}
	catch (std::ifstream::failure error) {
		std::cout << "Failed to read from file: " << filepath << std::endl;
		return std::string();
	}
	return contents.str();
}

bool Shader::Failed() {
	return failed_;
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
