#include "Sprite.h"
namespace SE {
	auto Sprite::Draw()->void
	{
		glEnable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0+m_texture.getID());
		m_vao.bind();
		m_ibo.bind();
		m_texture.bind();
		glDrawElements(GL_TRIANGLES, m_ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		m_ibo.unbind();
		m_vao.unbind();
		m_texture.unbind();
		glDisable(GL_DEPTH_TEST);
	}

	auto Sprite::getVAO() -> VertexArray
	{
		return m_vao;
	}

	auto Sprite::getIBO() -> IndexBuffer
	{
		return m_ibo;
	}

	auto Sprite::activateIBO(const std::vector<GLushort>& indexes)->void
	{

		m_ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	}

	auto Sprite::activateVAO(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& colors)->void
	{

		m_vao.addBuffer(std::make_shared<Buffer>(matrix, matrix.size(), 2), 0);
		m_vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);
	}

	auto Sprite::activateVAO(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& textureCoord, const std::vector<GLfloat>& colors)
	{
		m_vao.addBuffer(std::make_shared<Buffer>(matrix, matrix.size(), 2), 0);
		m_vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);

		//add texture coord vector to buffer
		m_vao.addBuffer(std::make_shared<Buffer>(textureCoord, textureCoord.size(), 2), 2);
	}

	Sprite::Sprite()
	{
	}

	Sprite::Sprite(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& colors, const std::vector<GLushort>&indexes)
	{
		activateIBO(indexes);
		activateVAO(matrix, std::vector<GLfloat>(m_texture.textures.begin(),m_texture.textures.end()),colors);
	}

	Sprite::Sprite(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& colors, const Texture & texture, const std::vector<GLushort>& indexes):m_texture(texture)
	{
		glActiveTexture(GL_TEXTURE0+m_texture.getID());
		activateIBO(indexes);
		activateVAO(matrix, std::vector<GLfloat>(m_texture.textures.begin(),m_texture.textures.end()),colors);
	}
}
