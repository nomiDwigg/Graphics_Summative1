// library
//local
// this
#include "Camera.h"

Camera::Camera(void) {}
Camera::~Camera(void) {}

glm::vec3*
Camera::m_camPos = new glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3*
Camera::m_camLookDir = new glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3*
Camera::m_camUpDir = new glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4*
Camera::m_viewMatrix = new glm::mat4;
glm::mat4*
Camera::m_projectionMatrix = new glm::mat4;

void 
Camera::initialise(float width, float height)
{
	*m_projectionMatrix = glm::ortho(width / -2.0f, width / 2.0f, height / -2.0f, height / 2.0f, 0.0f, 100.0f);
	*m_viewMatrix = glm::lookAt(*m_camPos, *m_camPos + *m_camLookDir, *m_camUpDir);
}

glm::mat4*
Camera::getViewMatrix()
{
	return(m_viewMatrix);
}

glm::mat4*
Camera::getProjectionMatrix()
{
	return(m_projectionMatrix);
}