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
#include <cmath>

// local
#include "MeshManager.h"
#include "Utility.h"
#include "Texture.h"

class Kanye
{
public:
	Kanye()
	{
		GLuint tex = Texture::createTexture("Resources/Textures/YoungKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE0, tex, "tex0"));
		tex = Texture::createTexture("Resources/Textures/NowKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint, const char*>(GL_TEXTURE1, tex, "tex1"));

		mixValue = 0;
	}

	~Kanye() {}

protected:
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
		mixValue = (-(cosf(3.14159f * Utility::m_currentTime)) / 2.0f) + 0.5f;
	}

private:
	std::vector<std::tuple<GLenum, GLuint, const char*>> m_textureInfo;
	float mixValue;
};

#endif   // __SCENE_OBJECTS_H__
