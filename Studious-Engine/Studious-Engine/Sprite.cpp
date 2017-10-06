#include "Sprite.h"
Sprite::Sprite(GLfloat pos1, GLfloat pos2, GLfloat pos3, GLfloat pos4, GLfloat R, GLfloat G, GLfloat B)
{
	m_pos1 = pos1;
	m_pos2 = pos2;
	m_pos3 = pos3;
	m_pos4 = pos4;
	ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	matrixPosition = { 0,0,0,m_pos1,m_pos2,m_pos3,m_pos4,0 };
	colors = { R,G,B,1.0f,R,G,B,1.0f,R,G,B,1.0f,R,G,B,1.0f };
	//ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	vao.addBuffer(std::make_shared<Buffer>(matrixPosition, matrixPosition.size(), 2), 0);
	vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);

}


auto Sprite::UpdateLocation(const GLfloat pos1, const GLfloat pos2, const  GLfloat pos3, const  GLfloat pos4)->void
{

	m_pos1 = pos1;
	m_pos2 = pos2;
	m_pos3 = pos3;
	m_pos4 = pos4;
	matrixPosition[3] = m_pos1;
	matrixPosition[4] = m_pos2;
	matrixPosition[5] = m_pos3;
	matrixPosition[6] = m_pos4;
	vao.addBuffer(std::make_shared<Buffer>(matrixPosition, matrixPosition.size(), 2), 0);
}

auto Sprite::UpdateLocation(const vec3 & position) -> void
{
	this->position = position;
}

auto Sprite::UpdateLocation(const vec3 & position, const unsigned priority) -> void
{
	this->position = position;
	m_priority = priority;
}

auto Sprite::Draw()->void
{

	vao.bind();
	ibo.bind();
	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
	ibo.unbind();
	vao.unbind();
}

auto Sprite::getPosition() const -> vec4
{
	return m_position;
}
auto Sprite::getColor() const -> vec3
{
	return m_color;
}
auto Sprite::getPriority() const -> unsigned
{
	return m_priority;
}
Sprite::Sprite(const vec4 & position, const vec3 & color, const unsigned priority):m_position(position),m_color(color),m_priority(priority)
{
	ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	matrixPosition = { 0,0,0,position.x,position.y,position.z,position.w,0 };
	colors = { color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f };
	//ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	vao.addBuffer(std::make_shared<Buffer>(matrixPosition, matrixPosition.size(), 2), 0);
	vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);
}

Sprite::Sprite(const vec3 & position, const float dim1, const float dim2, const vec3& color,const unsigned priority)
{
	this->position = position;
	ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	matrixPosition = { 0,0,0,dim2,dim1,dim2,dim1,0 };
	colors = { color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f };
	//ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	vao.addBuffer(std::make_shared<Buffer>(matrixPosition, matrixPosition.size(), 2), 0);
	vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);
}
