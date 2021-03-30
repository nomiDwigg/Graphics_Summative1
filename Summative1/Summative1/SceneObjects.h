#pragma once

#ifndef __SCENE_OBJECTS_H__
#define __SCENE_OBJECTS_H__

// this header file stores all the specific data for each type of object in the scene. all the specific texture,
// positional, and shader data is stored here for the so that the object class can access it if needed

// Dependencies
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// library
#include <utility>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

// local
#include "MeshManager.h"
#include "Utility.h"
#include "Texture.h"
#include "Shader.h"

class Kanye
{
public:

protected:
	Kanye() {}
	~Kanye() {}

	void initializeKanye()
	{
		// creating the textures needed for the kanye hexagon
		GLuint tex = Texture::createTexture("Resources/Textures/YoungKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE0, tex, "tex0"));
		tex = Texture::createTexture("Resources/Textures/NowKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE1, tex, "tex1"));

		mixValue = 0.0f;
	}

	// setting mesh and program data
	GLuint m_programKanye = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/doubleTexture.fs");
	//const char* m_vertexKanye = "Resources/Shaders/basic.vs";
	//const char* m_fragmentKanye = "Resources/Shaders/doubleTexture.fs";
	std::pair<GLuint, int> m_meshKanye = MeshManager::createMesh(Shape::HEXAGON);

	// setting positional data
	glm::vec3 m_posKanye = glm::vec3(-75.0f, 150.0f, 0.0f);
	glm::vec3 m_scaleKanye = glm::vec3(150.0f, 150.0f, 0.0f);
	float m_rotationDegreesKanye = 0.0f;

	// this function stores all the specific texture data that this hexagon will need
	void passUniformDataKanye(GLuint* program)
	{
		// passes the correct texture data to the fragment shader. data is stored in the texture info vector
		for (unsigned int tex = 0; tex < m_textureInfo.size(); tex++)
		{
			glActiveTexture(std::get<0>(m_textureInfo[tex]));
			glBindTexture(GL_TEXTURE_2D, std::get<1>(m_textureInfo[tex]));
			Utility::createUniforms<int>(std::get<2>(m_textureInfo[tex]), tex, program);
		}

		// passes the mix value to the fragment shader to smoothly interpolate between the two textures
		Utility::createUniforms<float>("mixValue", mixValue, program);
	}

	// update changes the mix value based on time to smoothly interpolate between two textures
	void update()
	{
		mixValue = (-(cosf(glm::pi<float>() * Utility::m_currentTime)) / 2.0f) + 0.5f;
	}

private:
	std::vector<std::tuple<GLenum, GLuint, const char*>> m_textureInfo;
	float mixValue = 0.0f;
};


class VEnergy
{
public:

protected:

	VEnergy() {}

	~VEnergy() {}

	void initializeV()
	{
		for (int frame = 0; frame < 6; frame++)
		{
			// generating each texture
			std::string path = "Resources/Textures/V_Energy/Frame" + std::to_string(frame);
			path += ".jpg";
			GLuint tex = Texture::createTexture(path.c_str());
			//GLenum active = GL_TEXTURE0 + frame;
			m_textureInfo.push_back(tex);
		}

		m_frameTimer = 0.0f;
		m_currentFrame = 0;
	}
	//const char* m_vertexV = "Resources/Shaders/basic.vs";
	//const char* m_fragmentV = "Resources/Shaders/basic.fs";

	GLuint m_programV = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	std::pair<GLuint, int> m_meshV = MeshManager::createMesh(Shape::HEXAGON);

	glm::vec3 m_posV = glm::vec3(-75.0f, -150.0f, 0.0f);
	glm::vec3 m_scaleV = glm::vec3(150.0f, 150.0f, 0.0f);
	float m_rotationV = 0.0f;

	void passUniformDataV(GLuint* program)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textureInfo[m_currentFrame]);
		Utility::createUniforms<int>("tex", m_currentFrame, program);
	}

	void update()
	{
		if (m_frameTimer < 0.07f)
		{
			m_frameTimer += Utility::getDeltaTime() / 0.001f;
		}
		else
		{
			m_currentFrame = (m_currentFrame >= 5) ? 0 : m_currentFrame + 1;
			m_frameTimer = 0.0f;
		}

		//std::cout << "Frame: " << m_currentFrame << "   :   Tex: " << std::get<1>(m_textureInfo[m_currentFrame]) << std::endl;
		//std::cout << "Frame: " << m_currentFrame << "   :   Active: " << std::get<0>(m_textureInfo[m_currentFrame]) << std::endl;

		//std::cout << "m_frameTimer = " << m_frameTimer << std::endl;
		//std::cout << "current frame = " << m_currentFrame << std::endl << std::endl;
	}

private:
	std::vector<GLuint> m_textureInfo;
	float m_frameTimer = 0.0f;
	int m_currentFrame = 0;
};

#endif   // __SCENE_OBJECTS_H__
