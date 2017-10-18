#include "Texture.h"

Texture::Texture(const std::string& fileName)
	: m_fileName(fileName)
{
	m_textureID = load();
	textures = {
	0,1,0,0,1,0,1,1
	};
}


Texture::~Texture()
{

}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::getID() -> GLuint const
{
	return m_textureID;
}

const GLsizei Texture::getWidth() const
{
	return m_width;
}

const GLsizei Texture::getHeight() const
{
	return m_height;
}

auto Texture::getNullTexture() -> Texture
{
	static Texture nullTexture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\nothing.png");
	return nullTexture;
}


GLuint Texture::load()
{
	BYTE* pixels = load_image(m_fileName.c_str(), &m_width, &m_height);
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	return result;
}