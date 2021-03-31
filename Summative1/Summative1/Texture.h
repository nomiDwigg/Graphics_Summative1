#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//dependencies
#include <glew.h>
#include <glfw3.h>

// library
#include <map>
#include <vector>

class Texture
{
public:
	Texture(void);
	~Texture(void);

	static GLuint* createTexture(std::string filepath);

private:
	static std::map<std::string, GLuint*> m_textureMap;
};
#endif   // __TEXTURE_H__

