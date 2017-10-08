#include "Sprite.h"

auto Sprite::UpdateLocation(const vec3 & position) -> void
{
	this->m_position = position;
	//std::cout << position.x << " " << position.y << " " << position.z << " ======= ";
	//std::cout << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
}

auto Sprite::UpdateLocation(const vec3 & position, const unsigned priority) -> void
{
	this->m_position = position;
	m_priority = priority;
}

auto Sprite::Draw()->void
{

	m_vao.bind();
	ibo.bind();
	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
	ibo.unbind();
	m_vao.unbind();
}

auto Sprite::getPosition() const -> vec3
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

auto Sprite::action() -> void
{
	float inc = -5.0f;
	this->UpdateLocation(this->m_position.add(vec3(-inc*0.1f, -inc* 0.1f, 0.0f)));
	if (this->m_position.y > 200 || this->m_position.y < 0)
		inc = -inc;
}


Sprite::Sprite(const vec3 & position, const vec2& dimension, const vec3& color,const unsigned priority):m_position(position),m_priority(priority)
{
	ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
	matrixPosition = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
	colors = { color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f };
	m_vao.addBuffer(std::make_shared<Buffer>(matrixPosition, matrixPosition.size(), 2), 0);
	m_vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);
}
