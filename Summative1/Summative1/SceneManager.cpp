// library
// local
// this
#include "SceneManager.h"

SceneManager::SceneManager()
{
	// default constructor
}

SceneManager::~SceneManager()
{
	// clean up memory by deleting all pointers to objects in scene
	while (m_sceneObjects.size() > 0)
	{
		Object* temp = m_sceneObjects[m_sceneObjects.size() - 1];
		m_sceneObjects.pop_back();
		delete temp;
	}
}


// this function is where all the objects that are present in the scene are created. they are then pushed into the
// scene objects vector to make rendering and updating each object simpler
void
SceneManager::initialize()
{
	m_sceneObjects.push_back(new Object(ObjectType::KANYE));
	m_sceneObjects.push_back(new Object(ObjectType::VENERGY));
	m_sceneObjects.push_back(new Object(ObjectType::WALK));
}

// renders all objects in the scene objects vector
void
SceneManager::render()
{
	for (unsigned int obj = 0; obj < m_sceneObjects.size(); obj++)
	{
		m_sceneObjects[obj]->render();
	}
}

// updates all objects in the scene object vector
void
SceneManager::update()
{
	for (unsigned int obj = 0; obj < m_sceneObjects.size(); obj++)
	{
		m_sceneObjects[obj]->update();
	}
}
