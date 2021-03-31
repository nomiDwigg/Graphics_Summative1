#pragma once

#ifndef __SHADER_H__
#define __SHADER_H__

// dependencies
#include <glew.h>
#include <glfw3.h>

// library
#include <iostream>
#include <map>

class Shader
{
public:
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);

private:
	Shader(void);
	~Shader(void);

	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	static std::string ReadShaderFile(const char* filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);

	static std::map<std::string, GLuint> uniqueIDs;  // a map storing all programs and shaders created
};

#endif   // __SHADER_H__
