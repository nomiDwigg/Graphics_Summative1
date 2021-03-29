#pragma once

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

//dependencies
#include <glew.h>
#include <glfw3.h>

//library
#include <vector>

//local
#include "Object.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void initialize();
	void render();
	void update();

private:
	std::vector<Object*> m_sceneObjects;  // vector of objects present in the scene
};
#endif   //__SCENE_MANAGER_H__
