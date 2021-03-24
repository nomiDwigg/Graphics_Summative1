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
	std::vector<Object*> m_sceneObjects;
};
#endif   //__SCENE_MANAGER_H__
