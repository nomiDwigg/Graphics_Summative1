#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

// Dependencies
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(void);
	~Camera(void);

	static void initialise(float width, float height);
	static glm::mat4* getViewMatrix();
	static glm::mat4* getProjectionMatrix();

	static glm::vec3* m_camPos;        // global camera position
	static glm::vec3* m_camLookDir;    // direction camera is pointing in / looking at
	static glm::vec3* m_camUpDir;      // the up vector / +y vector of the camera

private:
	static glm::mat4* m_viewMatrix;
	static glm::mat4* m_projectionMatrix;
};

#endif   // __CAMERA_H__

