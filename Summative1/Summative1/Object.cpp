// local
#include "Shader.h"

// this
#include "Object.h"

Object::Object(ObjectType type)
{
	m_program = new GLuint();
	m_mesh = std::pair<GLuint, int>(0, 0);

	m_objType = type;
	switch (type)
	{
	case ObjectType::KANYE:
	{
		m_program = new GLuint(Shader::CreateProgram(m_vertexKanye, m_fragmentKanye));
		m_mesh = m_meshKanye;
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
}
