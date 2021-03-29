#pragma once

#ifndef __UTILITY_H__
#define __UTILITY_H__

//dependencies
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//library
#include <iostream>
#include <tuple>

//local

class Utility
{
public:
	Utility(void);
	~Utility(void);

	// debugger from https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/1.debugging/debugging.cpp
	static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, 
		const GLchar* message, const void* userParam);

	// time variables and functions
	static void manageTime(float curr);
	static float getDeltaTime();
	static float m_currentTime, m_prevTime;

	// this function enables all uniforms to be created from one function call. this function also checks to make sure
	// the value of the uniform is valid before creating the uniform
	template<typename UniformType>
	static void createUniforms(const char* name, UniformType uniValue, GLuint* program)
	{
		// this prints out wheter or not the location is valid before specifiying the uniform value
		GLint uniformLocation = glGetUniformLocation(*program, name);

		if (uniformLocation < 0)
		{
			std::cout << "Uniform Location for " << name << " is INVALID." << std::endl << std::endl;
		}

		createUniPart(uniformLocation, uniValue);
	}

private:
	static float m_deltaTime;

	// these functions are used to allow one function to create all types of uniforms. a function for each uniform value type
	// is declared and defined here as to not clutter in other parts of the program
	template<typename UniformType> static void createUniPart(GLint location, UniformType uniValue)
	{
		std::cout << "ERROR: tried to create Uniform with invalid UniformType" << std::endl;
	}
	template<> static void createUniPart<int>(GLint location, int uniValue)
	{
		glUniform1i(location, uniValue);
	}
	template<> static void createUniPart<float>(GLint location, float uniValue)
	{
		glUniform1f(location, uniValue);
	}
	template<> static void createUniPart<glm::mat4>(GLint location, glm::mat4 uniValue)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniValue));
	}
};

#endif   // __UTILITY_H__
