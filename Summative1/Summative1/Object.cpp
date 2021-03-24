// local
#include "Shader.h"
#include "Camera.h"

// this
#include "Object.h"

Object::Object(ObjectType type)
{
	m_program = new GLuint();
	m_mesh = std::pair<GLuint, int>(0, 0);

	m_mvp = new glm::mat4;

	m_objType = type;
	switch (type)
	{
	case ObjectType::KANYE:
	{
		m_program = new GLuint(Shader::CreateProgram(m_vertexKanye, m_fragmentKanye));
		m_mesh = m_meshKanye;

		// set positional data for camera
		m_pos = &m_posKanye;
		m_rot = &m_rotationDegreesKanye;
		m_scale = &m_scaleKanye;
		break;
	}
	default:
		break;
	}
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
	default: break;
	}
	glDrawElements(GL_TRIANGLES, std::get<1>(m_mesh), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void
Object::update()
{
	switch (m_objType)
	{
	case ObjectType::KANYE: {Kanye::update(); break; }
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