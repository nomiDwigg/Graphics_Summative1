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
		m_mesh = m_meshKanye;

		initializeKanye();

		// set positional data for camera
		m_pos = &m_posKanye;
		m_rot = &m_rotationDegreesKanye;
		m_scale = &m_scaleKanye;
		break;
	}
	case ObjectType::VENERGY:
	{
		m_program = &m_programV;//new GLuint(Shader::CreateProgram(m_vertexV, m_fragmentV));
		m_mesh = m_meshV;

		initializeV();

		// set positional data for camera
		m_pos = &m_posV;
		m_rot = &m_rotationV;
		m_scale = &m_scaleV;
		break;
	}
	default:
	{
		m_program = new GLuint();
		m_mesh = std::pair<GLuint, int>(0, 0);

		std::cout << "ERROR: Object Type Invalid" << std::endl << std::endl;
		break;
	}
	}

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
	default: break;
	}

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