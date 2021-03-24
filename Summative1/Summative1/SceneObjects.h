#pragma once

#ifndef __SCENE_OBJECTS_H__
#define __SCENE_OBJECTS_H__

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

// local
#include "MeshManager.h"
#include "Utility.h"
#include "Texture.h"

class Kanye
{
public:

protected:
	Kanye()
	{
		GLuint tex = Texture::createTexture("Resources/Textures/YoungKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE0, tex, "tex0"));
		tex = Texture::createTexture("Resources/Textures/NowKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE1, tex, "tex1"));

		mixValue = 0;
	}

	~Kanye() {}

	const char* m_vertexKanye = "Resources/Shaders/basic.vs";
	const char* m_fragmentKanye = "Resources/Shaders/doubleTexture.fs";
	std::pair<GLuint, int> m_meshKanye = MeshManager::createMesh(Shape::HEXAGON);

	glm::vec3 m_posKanye = glm::vec3(-75.0f, 150.0f, 0.0f);
	glm::vec3 m_scaleKanye = glm::vec3(150.0f, 150.0f, 0.0f);
	float m_rotationDegreesKanye = 0.0f;

	void passUniformDataKanye(GLuint* program)
	{
		for (unsigned int tex = 0; tex < m_textureInfo.size(); tex++)
		{
			glActiveTexture(std::get<0>(m_textureInfo[tex]));
			glBindTexture(GL_TEXTURE_2D, std::get<1>(m_textureInfo[tex]));
			Utility::createUniforms<int>(std::get<2>(m_textureInfo[tex]), tex, program);
		}

		Utility::createUniforms<float>("mixValue", mixValue, program);
	}

	void update()
	{
		mixValue = (-(cosf(glm::pi<float>() * Utility::m_currentTime)) / 2.0f) + 0.5f;
	}

private:
	std::vector<std::tuple<GLenum, GLuint, const char*>> m_textureInfo;
	float mixValue;
};


class VEnergy
{
public:

protected:

	VEnergy()
	{
		for (GLuint frame = 0; frame < 6; frame++)
		{
			// generating each texture
			std::string path = "Resources/Textures/V_Energy/Frame" + std::to_string(frame);
			path += ".jpg";
			GLuint tex = Texture::createTexture(path.c_str());

			m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE0, tex, "tex"));
		}

		m_frameTimer = 0;
		m_currentFrame = 0;
	}

	~VEnergy(){}

	const char* m_vertexV = "Resources/Shaders/basic.vs";
	const char* m_fragmentV = "Resources/Shaders/basic.fs";
	std::pair<GLuint, int> m_meshV = MeshManager::createMesh(Shape::HEXAGON);

	glm::vec3 m_posV = glm::vec3(-75.0f, -150.0f, 0.0f);
	glm::vec3 m_scaleV = glm::vec3(150.0f, 150.0f, 0.0f);
	float m_rotationV = 0.0f;

	void passUniformDataV(GLuint* program)
	{
		glActiveTexture(std::get<0>(m_textureInfo[m_currentFrame]));
		glBindTexture(GL_TEXTURE_2D, std::get<1>(m_textureInfo[m_currentFrame]));
		Utility::createUniforms(std::get<2>(m_textureInfo[m_currentFrame]), m_currentFrame, program);
	}

	void update()
	{
		if (m_frameTimer < 3.0f)
		{
			m_frameTimer += Utility::getDeltaTime();
		}
		else
		{
			m_currentFrame = (m_currentFrame >= 5) ? 0 : m_currentFrame + 1;
			m_frameTimer = 0.0f;
		}
	}

private:
	std::vector<std::tuple<GLenum, GLuint, const char*>> m_textureInfo;
	float m_frameTimer;
	int m_currentFrame;
};

#endif   // __SCENE_OBJECTS_H__
