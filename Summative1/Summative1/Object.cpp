// library
#include <iostream>

// local
#include "Shader.h"
#include "Camera.h"

// this
#include "Object.h"

// using the specific object type, the constructor will create an instance of the object class and populate it with
// data from the correct base class
Object::Object(ObjectType type)
{
	m_objType = type;
	switch (type)
	{
	case ObjectType::KANYE:
	{
		m_program = &m_programKanye;//new GLuint(Shader::CreateProgram(m_vertexKanye, m_fragmentKanye));

		initializeKanye();
		m_mesh = m_meshKanye;
		m_shapeType = m_shapeKanye;

		// set positional data for camera
		m_pos = &m_posKanye;
		m_rot = &m_rotationDegreesKanye;
		m_scale = &m_scaleKanye;

		m_texCoords = m_texCoordsKanye;
		break;
	}
	case ObjectType::VENERGY:
	{
		m_program = &m_programV;//new GLuint(Shader::CreateProgram(m_vertexV, m_fragmentV));

		initializeV();
		m_mesh = m_meshV;
		m_shapeType = m_shapeV;

		// set positional data for camera
		m_pos = &m_posV;
		m_rot = &m_rotationV;
		m_scale = &m_scaleV;

		m_texCoords = m_texCoordsV;
		break;
	}
	case ObjectType::WALK:
	{
		m_program = &m_programWalk;//new GLuint(Shader::CreateProgram(m_vertexV, m_fragmentV));

		initializeWalk();
		m_mesh = m_meshWalk;
		m_shapeType = m_shapeWalk;

		// set positional data for camera
		m_pos = &m_posWalk;
		m_rot = &m_rotationWalk;
		m_scale = &m_scaleWalk;

		m_texCoords = m_texCoordsWalk;
		break;
	}
	default:
	{
		m_program = new GLuint();
		m_mesh = std::pair<GLuint, int>(0, 0);
		m_texCoords = m_texCoordsKanye;
		m_shapeType = m_shapeKanye;

		std::cout << "ERROR: Object Type Invalid" << std::endl << std::endl;
		break;
	}
	}

	//MeshManager::editMesh(m_shapeType, m_texCoords);
	m_mvp = new glm::mat4;
}

Object::~Object()
{

}


void
Object::render()
{
	glUseProgram(*m_program);
	glBindVertexArray(std::get<0>(m_mesh));

	// send MVP to vertex
	Utility::createUniforms("MVP", *m_mvp, m_program);

	// send variables to fragment shaders
	switch (m_objType)
	{
	case ObjectType::KANYE: { passUniformDataKanye(m_program); break; }
	case ObjectType::VENERGY: { passUniformDataV(m_program); break; }
	case ObjectType::WALK: { passUniformDataWalk(m_program); break; }
	default: 
		break;
	}
	glDrawElements(GL_TRIANGLES, std::get<1>(m_mesh), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void
Object::update()
{
	switch (m_objType)
	{
	case ObjectType::KANYE: {Kanye::update(); break; }
	case ObjectType::VENERGY: {VEnergy::update(); break; }
	case ObjectType::WALK: {Walk::update(); break; }
	default: break;
	}

	//MeshManager::editMesh(m_shapeType, m_texCoords);
	calculateMVP();
}

void 
Object::calculateMVP()
{
	glm::mat4 trans = glm::translate(glm::mat4(), *m_pos);
	glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(*m_rot), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scale = glm::scale(glm::mat4(), *m_scale);

	*m_mvp = *Camera::getProjectionMatrix() * *Camera::getViewMatrix() * trans * rotate * scale;
}