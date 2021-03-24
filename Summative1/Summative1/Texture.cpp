// dependencies
#include <stb_image.h>

// this
#include "Texture.h"

Texture::Texture(void) {}
Texture::~Texture(void) {}

std::map<const char*, GLuint>
Texture::m_textureMap;

GLuint
Texture::createTexture(const char* filepath)
{
	// check that texture hasnt been created already
	std::map<const char*, GLuint>::iterator iterTexture = m_textureMap.find(filepath);
	if (iterTexture != m_textureMap.end())
	{
		return(m_textureMap[filepath]);
	}
	else
	{
		// load image data
		int width, height, components;
		unsigned char* imageData = stbi_load(filepath, &width, &height, &components, 0);

		// create and bind a new texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// check how many components the loaded image has
		GLint loadedComponents = (components == 4) ? GL_RGBA : GL_RGB;

		// populate the texture with the image data
		glTexImage2D(GL_TEXTURE_2D, 0, loadedComponents, width, height, 0, 
			loadedComponents, GL_UNSIGNED_BYTE, imageData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// generate the mipmaps, free the memory and unbind the texture
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureMap.insert(std::pair<const char*, GLuint>(filepath, texture));
		return(texture);
	}
}
