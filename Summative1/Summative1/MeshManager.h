#pragma once

#ifndef __MESH_MANAGER_H__
#define __MESH_MANAGER_H__

// Dependencies
#include <glew.h>
#include <glfw3.h>

// library
#include <map>

enum class Shape  // enum for all possible shape types
{
	TRIANGLE = 0,
	QUAD = 1,
	HEXAGON = 2
};

class MeshManager
{
public: 
	MeshManager(void);
	~MeshManager(void);

	static std::pair<GLuint, int> createMesh(Shape shape);
	//static void editMesh()
private:

	static std::map<Shape, std::pair<GLuint, int>> m_createdMeshes;  // map of all created meshes

	static GLfloat m_triVertices[24];
	static GLuint m_triIndices[3];
	static GLfloat m_quadVertices[32];
	static GLuint m_quadIndices[6];
	static GLfloat m_hexVertices[48];
	static GLuint m_hexIndices[12];
};

#endif    // __MESH_MANAGER_H__
