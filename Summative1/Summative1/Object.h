#pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__

// dependencies
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// library
// local
#include "SceneObjects.h"


// custom variables
enum class ObjectType
{
	KANYE = 0,
	VENERGY = 1,
	WALK = 2,
	SPIRAL = 3,
	DUCK = 4
};

class Object : public Kanye, public VEnergy, public Walk, public Spiral, public Duck
{
public:
	Object(ObjectType type);
	~Object();

	void render();
	void update();

	glm::vec3* m_pos;
	float* m_rot;
	glm::vec3* m_scale;

private:
	GLuint* m_program;
	std::pair<GLuint, int> m_mesh;  // VAO, IndicesNum

	ObjectType m_objType;
	Shape m_shapeType;

	void calculateMVP();

	glm::mat4* m_mvp;

	// the tex coord data
	std::vector<glm::vec2> m_texCoords;
};

#endif   // __OBJECT_H__
