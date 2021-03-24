// library
// local
// this
#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	while (m_sceneObjects.size() > 0)
	{
		Object* temp = m_sceneObjects[m_sceneObjects.size() - 1];
		m_sceneObjects.pop_back();
		delete temp;
	}
}


void
SceneManager::initialize()
{
	m_sceneObjects.push_back(new Object(ObjectType::KANYE));
}

void
SceneManager::render()
{
	for (unsigned int obj = 0; obj < m_sceneObjects.size(); obj++)
	{
		m_sceneObjects[obj]->render();
	}
}

void
SceneManager::update()
{
	for (unsigned int obj = 0; obj < m_sceneObjects.size(); obj++)
	{
		m_sceneObjects[obj]->update();
	}
}
