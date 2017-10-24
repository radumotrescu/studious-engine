#pragma once

#include<FreeImage.h>
#include <string>
#include <glew.h>
#include <array>


class Texture 
{
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

	auto getID() const ->GLuint;

	GLsizei getWidth() const;
	GLsizei getHeight() const;

	static auto getNullTexture()->Texture;
private:
	GLuint load();
	static auto load_image(const char* filename, GLsizei* width, GLsizei* height)->BYTE*;
};

