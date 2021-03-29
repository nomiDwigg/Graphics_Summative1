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

	static GLuint createTexture(const char* filepath);

private:
	static std::map<const char*, GLuint> m_textureMap;
};
#endif   // __TEXTURE_H__

