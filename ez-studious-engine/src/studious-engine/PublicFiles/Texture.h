#pragma once

#include <string>
#include <glew.h>
#include "ImageLoad.h"

class Texture
{
private:
	std::string m_fileName;
	GLuint m_textureID;           //m_TID
	GLsizei m_width, m_height;
public:
	Texture(const std::string& fileName);
	Texture() {};
	~Texture();
	void bind() const;
	void unbind() const;

	auto getID()->GLuint const;

	const GLsizei getWidth() const;
	const GLsizei getHeight() const;
private:
	GLuint load();
};

/*
Texture texture("test.png");
Simple2DRenderer simple;
Sprite* testTexture = new Sprite(0, 0, 4, 4, maths::vec4(1, 1, 1, 1));
while(!window.closed())
{
simple.submit(testTexture);
simple.flush();
}
*/
