#pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__

// dependencies
#include <glew.h>
#include <glfw3.h>

// library
// local
#include "SceneObjects.h"


// custom variables
enum class ObjectType
{
	KANYE = 0
};

class Object : public Kanye
{
public:
	Object(ObjectType type);
	~Object();

	void render();
	void update();

protected:
	GLuint* m_program;
	std::pair<GLuint, int> m_mesh;  // VAO, IndicesNum

private:
	ObjectType m_objType;
};

#endif   // __OBJECT_H__
