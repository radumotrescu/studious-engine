#include "Sprite.h"
namespace SE {
	auto Sprite::Draw()->void
	{
		glEnable(GL_DEPTH_TEST);
		m_vao.bind();
		m_ibo.bind();
		glDrawElements(GL_TRIANGLES, m_ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		m_ibo.unbind();
		m_vao.unbind();
		glDisable(GL_DEPTH_TEST);
	}



	//auto Sprite::action() -> void
	//{
	//	float inc = -5.0f;
	//	this->UpdateLocation(this->m_position.add(vec3(-inc*0.1f, -inc* 0.1f, 0.0f)));
	//	if (this->m_position.y > 200 || this->m_position.y < 0)
	//		inc = -inc;
	//}

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
		activateVAO(matrix, colors);
	}

	Sprite::Sprite(const std::vector<GLfloat>& matrix, const std::vector<GLfloat>& colors, const std::vector<GLfloat>& textureCoord, const std::vector<GLushort>& indexes)
	{
		activateIBO(indexes);
		activateVAO(matrix, textureCoord, colors);
	}

}
