#pragma once

#include <string>
#include <glew.h>
#include "ImageLoad.h"
#include <array>

class Texture {
private:
	std::string m_fileName;
	GLuint m_textureID; 
	GLsizei m_width, m_height;
public:
	
	std::array<GLfloat, 8> textures;
	int activeTextureID=0;

	Texture(const std::string& fileName);
	Texture() {};
	~Texture();
	void bind() const;
	void unbind() const;

	auto getID()->GLuint const;

	const GLsizei getWidth() const;
	const GLsizei getHeight() const;

	static auto getNullTexture()->Texture;
private:
	GLuint load();
};

