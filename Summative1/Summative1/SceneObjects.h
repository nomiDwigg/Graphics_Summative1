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
		GLuint* tex = Texture::createTexture("Resources/Textures/YoungKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint*, const char*>(GL_TEXTURE0, tex, "tex0"));
		tex = Texture::createTexture("Resources/Textures/NowKanye.jpg");
		m_textureInfo.push_back(std::tuple<GLenum, GLuint*, const char*>(GL_TEXTURE1, tex, "tex1"));

		mixValue = 0.0f;

		// this makes sure the texture coordinates dont change for this shape 
		// if another shape using the same mesh needs to change the texture coords
		m_texCoordsKanye = { glm::vec4(-0.5f, 1.0f, 0.2f, 1.0f), glm::vec4(-1.0f, 0.0f, 0.0f, 0.5f), 
			glm::vec4(-0.5f, -1.0f, 0.2f, 0.0f), glm::vec4(0.5f, -1.0f, 0.8f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 0.5f),
			glm::vec4(0.5f, 1.0f, 0.8f, 1.0f) };
		MeshManager::editMesh(Shape::HEXAGON, m_texCoordsKanye);
		m_meshKanye = MeshManager::createMesh(Shape::HEXAGON);
	}

	// setting mesh and program data
	GLuint m_programKanye = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/doubleTexture.fs");
	std::pair<GLuint, int> m_meshKanye;
	Shape m_shapeKanye = Shape::HEXAGON;

	// setting positional data
	glm::vec3 m_posKanye = glm::vec3(-75.0f, 150.0f, 0.0f);
	glm::vec3 m_scaleKanye = glm::vec3(150.0f, 150.0f, 0.0f);
	float m_rotationDegreesKanye = 0.0f;
	
	// texture coordinate data
	std::vector<glm::vec4> m_texCoordsKanye;

	// this function stores all the specific texture data that this hexagon will need
	void passUniformDataKanye(GLuint* program)
	{
		// passes the correct texture data to the fragment shader. data is stored in the texture info vector
		for (unsigned int tex = 0; tex < m_textureInfo.size(); tex++)
		{
			glActiveTexture(std::get<0>(m_textureInfo[tex]));
			glBindTexture(GL_TEXTURE_2D, *std::get<1>(m_textureInfo[tex]));
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
	std::vector<std::tuple<GLenum, GLuint*, const char*>> m_textureInfo;
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
		for (int frame = 0; frame < 6; ++frame)
		{
			// generating each texture
			std::string path = "Resources/Textures/V_Energy/Frame" + std::to_string(frame);
			path += ".jpg";
			GLuint* tex = Texture::createTexture(path);
			//GLenum active = GL_TEXTURE0 + frame;
			m_textureInfo.push_back(tex);
		}

		m_frameTimer = 0.0f;
		m_currentFrame = 0;

		// this makes sure the texture coordinates dont change for this shape 
		// if another shape using the same mesh needs to change the texture coords
		m_texCoordsV = { glm::vec4(-0.3075f, 1.0f, 0.2f, 1.0f), glm::vec4(-0.615f, 0.0f, 0.0f, 0.5f),
			glm::vec4(-0.3075f, -1.0f, 0.2f, 0.0f), glm::vec4(0.3075f, -1.0f, 0.8f, 0.0f),
			glm::vec4(0.615f, 0.0f, 1.0f, 0.5f), glm::vec4(0.3075f, 1.0f, 0.8f, 1.0f) };
		MeshManager::editMesh(Shape::HEXAGON, m_texCoordsV);
		m_meshV = MeshManager::createMesh(Shape::HEXAGON);
	}

	// setting mesh and program data
	GLuint m_programV = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	std::pair<GLuint, int> m_meshV;
	Shape m_shapeV = Shape::HEXAGON;

	glm::vec3 m_posV = glm::vec3(-75.0f, -150.0f, 0.0f);
	glm::vec3 m_scaleV = glm::vec3(150.0f, 150.0f, 0.0f);
	float m_rotationV = 0.0f;

	// the tex coord data
	std::vector<glm::vec4> m_texCoordsV;

	void passUniformDataV(GLuint* program)
	{
		glActiveTexture(GL_TEXTURE0 + m_currentFrame);
		glBindTexture(GL_TEXTURE_2D, *m_textureInfo[m_currentFrame]);
		Utility::createUniforms<int>("tex", m_currentFrame, program);
	}

	void update()
	{
		m_frameTimer += Utility::getDeltaTime() / 0.001f;

		if(m_frameTimer >= 0.07f)
		{
			m_currentFrame = (m_currentFrame >= 5) ? 0 : m_currentFrame + 1;
			m_frameTimer = 0.0f;
		}
	}

private:
	std::vector<GLuint*> m_textureInfo;
	float m_frameTimer = 0.0f;
	int m_currentFrame = 0;
};

class Walk
{
public:

protected:

	Walk() {}
	~Walk() {}

	void initializeWalk()
	{
		// the tex coord data
		m_texCoordsWalk = { glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f), glm::vec4(-1.0f, -1.0f, 0.0f, 0.75f),
			glm::vec4(1.0f, -1.0f, (1.0f / 9.0f), 0.75f), glm::vec4(1.0f, 1.0f, (1.0f / 9.0f), 1.0f) };
		MeshManager::editMesh(Shape::QUAD, m_texCoordsWalk);
		m_meshWalk = MeshManager::createMesh(Shape::QUAD);

		m_texture = Texture::createTexture("Resources/Textures/SpriteSheet.png");
	}

	// mesh and program data
	GLuint m_programWalk = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/SpriteSheet.fs");
	std::pair<GLuint, int> m_meshWalk;
	Shape m_shapeWalk = Shape::QUAD;
	std::vector<glm::vec4> m_texCoordsWalk;

	// positional data
	glm::vec3 m_posWalk = glm::vec3(-550.0f, -350.0f, 0.0f);
	glm::vec3 m_scaleWalk = glm::vec3(50.0f, 50.0f, 0.0f);
	float m_rotationWalk = 0.0f;

	void update()
	{
		if ((m_posWalk.x <= -550.0f) && (m_posWalk.y <= -350.0f)) // hits bottom left corner 
		{ 
			// set new speed and frame data
			m_currentFrame = glm::vec2(0.0f, 0.0f);
			m_speed = glm::vec2(0.0f, 5.0f);
		}
		if ((m_posWalk.x <= -550.0f) && (m_posWalk.y >= 350.0f)) // hits top left corner 
		{
			// set new speed and frame data
			m_currentFrame = glm::vec2(0.0f, 0.25f);
			m_speed = glm::vec2(5.0f, 0.0f);
		}
		if ((m_posWalk.x >= 550.0f) && (m_posWalk.y >= 350.0f)) // hits top right corner 
		{
			// set new speed and frame data
			m_currentFrame = glm::vec2(0.0f, 0.5f);
			m_speed = glm::vec2(0.0f, -5.0f);
		}
		if ((m_posWalk.x >= 550.0f) && (m_posWalk.y <= -350.0f)) // hits bottom right corner 
		{
			// set new speed and frame data
			m_currentFrame = glm::vec2(0.0f, 0.75f);
			m_speed = glm::vec2(-5.0f, 0.0f);
		}

		m_frameTimer += Utility::getDeltaTime() / 0.001f;

		if (m_frameTimer >= 0.07f)
		{
			m_currentFrame.x = (m_currentFrame.x >= m_frameNum.x) ? 0.0f : m_currentFrame.x + (1.0f / 9.0f);
			m_frameTimer = 0.0f;

			//for (unsigned int point = 0; point < m_texCoordsWalk.size(); point++)
			//{
			//	m_texCoordsWalk[point].x += 1.0f / 9.0f;
			//}
		}

		//m_texCoordsWalk[1].y = m_currentFrame.y / 9.0f;
		//m_texCoordsWalk[2].y = m_currentFrame.y / 9.0f;
		//m_texCoordsWalk[0].y = (m_currentFrame.y / 9.0f) + m_texCoordsWalk[1].y;
		//m_texCoordsWalk[3].y = (m_currentFrame.y / 9.0f) + m_texCoordsWalk[1].y;

		m_posWalk += glm::vec3(m_speed, 0.0f);
	}

	void passUniformDataWalk(GLuint* program)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *m_texture);
		Utility::createUniforms<int>("tex", 0, program);
		Utility::createUniforms<glm::vec2>("coords", m_currentFrame, program);
	}

private:
	GLuint* m_texture = new GLuint();

	// frame data
	glm::vec2 m_frameNum = glm::vec2(9, 4);
	glm::vec2 m_currentFrame = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_speed = glm::vec2(0.0f, 0.0f);
	float m_frameTimer = 0.0f;

};

class Spiral
{
public:

protected:

	Spiral() {}
	~Spiral() {}

	void initializeSpiral()
	{
		//set up texture coords and create mesh
		m_texCoordsSpiral = { glm::vec4(0.0f, 0.85f, 0.5f, 1.0f), glm::vec4(-1.0f, -0.85f, 0.125f, 0.0f), 
			glm::vec4(1.0f, -0.85f, 1.0f, 0.875f) };
		MeshManager::editMesh(Shape::TRIANGLE, m_texCoordsSpiral);
		m_meshSpiral = MeshManager::createMesh(Shape::TRIANGLE);

		// set up texture
		m_texture = Texture::createTexture("Resources/Textures/Spiral.jpg");
	}

	// set up program and mesh data
	GLuint m_programSpiral = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	std::pair<GLuint, int> m_meshSpiral;
	Shape m_shapeSpiral = Shape::TRIANGLE;
	std::vector<glm::vec4> m_texCoordsSpiral;

	// positional data
	glm::vec3 m_posSpiral = glm::vec3(300.0f, 225.0f, 0.0f);
	glm::vec3 m_scaleSpiral = glm::vec3(100.0f, 100.0f, 0.0f);
	float m_rotationSpiral = 0.0f;

	void update()
	{
		m_rotationSpiral -= 1.0f;
	}

	void passUniformDataSpiral(GLuint* program)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *m_texture);
		Utility::createUniforms<int>("tex", 0, program);
	}

private:
	GLuint* m_texture = new GLuint();
};

class Duck
{
public:

protected:

	Duck() {}
	~Duck() {}

	void initializeDuck()
	{
		//set up texture coords and create mesh
		m_texCoordsDuck = { glm::vec4(0.0f, 0.85f, 0.5f, 1.0f), glm::vec4(-1.0f, -0.85f, 0.0f, 0.0f),
			glm::vec4(1.0f, -0.85f, 1.0f, 0.0f) };
		MeshManager::editMesh(Shape::TRIANGLE, m_texCoordsDuck);
		m_meshDuck = MeshManager::createMesh(Shape::TRIANGLE);

		// set up texture
		m_texture = Texture::createTexture("Resources/Textures/Duck.jpg");
	}

	// set up program and mesh data
	GLuint m_programDuck = Shader::CreateProgram("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	std::pair<GLuint, int> m_meshDuck;
	Shape m_shapeDuck = Shape::TRIANGLE;
	std::vector<glm::vec4> m_texCoordsDuck;

	// positional data
	glm::vec3 m_posDuck = glm::vec3(300.0f, 0.0f, 0.0f);
	glm::vec3 m_scaleDuck = glm::vec3(100.0f, 100.0f, 0.0f);
	float m_rotationDuck = 0.0f;

	void update()
	{
		if ((m_scaleDuck.x <= m_minScale) || (m_scaleDuck.x >= m_maxScale))
		{
			m_modify *= -1.0f;
		}

		m_scaleDuck.x += m_modify;
		m_scaleDuck.y += m_modify;
	}

	void passUniformDataDuck(GLuint* program)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *m_texture);
		Utility::createUniforms<int>("tex", 0, program);
	}

private:
	GLuint* m_texture = new GLuint();
	float m_maxScale = 200.0f, m_minScale = 25.0f;
	float m_modify = 1.0f;
};

#endif   // __SCENE_OBJECTS_H__
