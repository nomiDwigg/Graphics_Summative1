// library
#include <iostream>

// this include
#include "MeshManager.h"

MeshManager::MeshManager(void) {}
MeshManager::~MeshManager(void) {}

std::map<Shape, std::pair<GLuint, int>>
MeshManager::m_createdMeshes;

GLfloat
MeshManager::m_triVertices[24] = {
	// position           // colour          // texture
	 0.0f, 0.1f, 0.0f,   1.0f, 0.0f, 0.0f,   0.5f, 1.0f,  // top point
	-1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // left point
	 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // right point
};
GLuint
MeshManager::m_triIndices[3] = {
	0, 1, 2
};

GLfloat
MeshManager::m_quadVertices[32] = {
	// index     //position              //colour         // texture
	/* 0 */   -1.0f,  1.0f, 0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 1.0f, // Top Left
	/* 1 */   -1.0f, -1.0f, 0.0f,    0.0f, 1.0f, 0.5f,    0.0f, 0.0f, // bot left
	/* 2 */    1.0f, -1.0f, 0.0f,    0.5f, 0.0f, 1.0f,    1.0f, 0.0f, // bot right
	/* 3 */    1.0f,  1.0f, 0.0f,    0.0f, 0.5f, 1.0f,    1.0f, 1.0f  // top right
};
GLuint
MeshManager::m_quadIndices[6] = {
	0, 1, 2,   // first triangle (TL - BL - BR)
	0, 2, 3    // second triangle (TL - BR - TR)
};

GLfloat
MeshManager::m_hexVertices[48] = {
	// index        // position             // colour          // texture
	/* 0 */     -0.5f,   1.0f,  0.0f,    1.0f, 0.0f, 0.0f,     0.2f, 1.0f,   // top - left
	/* 1 */     -1.0f,   0.0f,  0.0f,    1.0f, 0.0f, 0.0f,     0.0f, 0.5f,   // middle - left
	/* 2 */     -0.5f,  -1.0f,  0.0f,    1.0f, 0.0f, 0.0f,     0.2f, 0.0f,   // bottom - left
	/* 3 */      0.5f,  -1.0f,  0.0f,    1.0f, 0.0f, 0.0f,     0.8f, 0.0f,   // bottom - right
	/* 4 */      1.0f,   0.0f,  0.0f,    1.0f, 0.0f, 0.0f,     1.0f, 0.5f,   // middle - right
	/* 5 */      0.5f,   1.0f,  0.0f,    1.0f, 0.0f, 0.0f,     0.8f, 1.0f    // top - right
};
GLuint
MeshManager::m_hexIndices[12] = {
	0, 1, 2,
	0, 2, 3,
	0, 3, 5,
	5, 3, 4
};

std::pair<GLuint, int>
MeshManager::createMesh(Shape shape)
{
	// create an iterator of the created mesh map and iterate through it to see if the mesh has already been created
	std::map<Shape, std::pair<GLuint, int>>::iterator iterMesh = m_createdMeshes.find(shape);
	if (iterMesh != m_createdMeshes.end()) // if the mesh has been created already, return it
	{
		return(m_createdMeshes[shape]);
	}
	else  // if the mesh has not been created, create it then add it to the map
	{
		GLuint vao, ebo = 0, vbo = 0;

		// generate and bind the vertex array object
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		switch (shape)
		{
		case Shape::TRIANGLE:
		{
			// generate and bind the element buffer object
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_triIndices), m_triIndices, GL_STATIC_DRAW);

			// generate and bind the vertex buffer object
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(m_triVertices), m_triVertices, GL_STATIC_DRAW);

			// set vertex attribute information
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);  // position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));  // colour
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));  // texture
			glEnableVertexAttribArray(2);

			// add the VAO and indice count to the created meshes map
			std::pair<GLuint, int> meshData(vao, 3);
			m_createdMeshes.insert(std::pair<Shape, std::pair<GLuint, int>>(Shape::TRIANGLE, meshData));
			return(meshData);
			break;
		}
		case Shape::QUAD:
		{
			// generate and bind the element buffer object
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_quadIndices), m_quadIndices, GL_STATIC_DRAW);

			// generate and bind the vertex buffer object
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(m_quadVertices), m_quadVertices, GL_STATIC_DRAW);

			// set vertex attribute information
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);  // position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));  // colour
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));  // texture
			glEnableVertexAttribArray(2);

			// add the VAO and indice count to the created meshes map
			std::pair<GLuint, int> meshData(vao, 6);
			m_createdMeshes.insert(std::pair<Shape, std::pair<GLuint, int>>(Shape::QUAD, meshData));
			return(meshData);
			break;
		}
		case Shape::HEXAGON:
		{
			// generate and bind the element buffer object
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_hexIndices), m_hexIndices, GL_STATIC_DRAW);

			// generate and bind the vertex buffer object
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(m_hexVertices), m_hexVertices, GL_STATIC_DRAW);

			// set vertex attribute information
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);  // position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));  // colour
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));  // texture
			glEnableVertexAttribArray(2);

			// add the VAO and indice count to the created meshes map
			std::pair<GLuint, int> meshData(vao, 12);
			m_createdMeshes.insert(std::pair<Shape, std::pair<GLuint, int>>(Shape::HEXAGON, meshData));
			return(meshData);
			break;
		}
		default:
		{
			std::cout << "Error: Shape was invalid in creating mesh" << std::endl;
			break;
		}
		}

		return(std::pair<GLuint, int>(0, 0));
	}
}

void 
MeshManager::editMesh(int shape_i, std::vector<glm::vec2> mod)
{
	Shape shape = static_cast<Shape>(shape_i);

	switch (shape)
	{
	case Shape::TRIANGLE:
	{
		for (unsigned int point = 0; point < mod.size(); point++)
		{
			m_triVertices[(point * 8) + 6] = mod[point].x;
			m_triVertices[(point * 8) + 7] = mod[point].y;
		}
		break;
	}
	case Shape::QUAD:
	{
		for (unsigned int point = 0; point < mod.size(); point++)
		{
			m_quadVertices[(point * 8) + 6] = mod[point].x;
			m_quadVertices[(point * 8) + 7] = mod[point].y;
		}
		break;
	}
	case Shape::HEXAGON:
	{
		for (unsigned int point = 0; point < mod.size(); point++)
		{
			m_hexVertices[(point * 8) + 6] = mod[point].x;
			m_hexVertices[(point * 8) + 7] = mod[point].y;
		}
		break;
	}
	default:
		break;
	}
}