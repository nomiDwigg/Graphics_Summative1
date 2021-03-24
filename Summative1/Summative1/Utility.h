#pragma once

#ifndef __UTILITY_H__
#define __UTILITY_H__

//dependencies
#include <glew.h>
#include <glfw3.h>

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

	// converts pair into tuple
	//static void setTuple(std::tuple)

	template<typename UniformType>
	static void createUniforms(const char* name, UniformType uniValue, GLuint* program)
	{
		// this prints out wheter or not the location is valid before specifiying the uniform value
		GLint uniformLocation = glGetUniformLocation(*program, name);

		if (uniformLocation < 0)
		{
			/*std::cout << "Uniform Location for " << name << " is INVALID. Object: "
				<< getEnumName<ObjectTypes>(static_cast<int>(m_objectType)) << "   Shape: "
				<< getEnumName<ShapeName>(static_cast<int>(m_shapeName)) << std::endl << std::endl;*/

			std::cout << "Uniform Location for " << name << " is INVALID." << std::endl << std::endl;
		}

		createUniPart(uniformLocation, uniValue);
	}

private:
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

	static float m_deltaTime;
};

#endif   // __UTILITY_H__
