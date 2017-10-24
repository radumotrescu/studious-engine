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

auto Texture::getID() const -> GLuint
{
	return m_textureID;
}

auto Texture::getWidth() const -> GLsizei
{
	return m_width;
}

auto Texture::getHeight() const -> GLsizei
{
	return m_height;
}

auto Texture::getNullTexture() -> Texture
{
	static Texture nullTexture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\nothing.png");
	return nullTexture;
}

BYTE* Texture::load_image(const char* filename, GLsizei* width, GLsizei* height)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = nullptr;
	fif = FreeImage_GetFileType(filename, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	if (fif == FIF_UNKNOWN)
		return nullptr;

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	if (!dib)
		return nullptr;

	BYTE* result = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);

	return result;
}

GLuint Texture::load()
{
	BYTE* pixels = Texture::load_image(m_fileName.c_str(), &m_width, &m_height);
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