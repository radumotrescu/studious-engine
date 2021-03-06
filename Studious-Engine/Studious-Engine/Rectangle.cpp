#include "Rectangle.h"

namespace stud {


	auto Rectangle::changePointCoordinates(const vec3 & position) -> void
	{
		m_origin = position;
	}

	auto Rectangle::changePriority(const unsigned priority) -> void
	{
		m_priority = priority;
	}

	Rectangle::Rectangle(const vec3 & position, const vec2 & dimension, const vec3 & color, const unsigned priority):m_origin(position),m_dimension(dimension),m_color(color),m_priority(priority)
	{
		matrix = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
		colors = { color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f };
		m_sprite = Sprite(matrix, colors, indexes);
	}

	auto Rectangle::getPriority() const -> unsigned
	{
		return m_priority;
	}
	const float move = 5.0;
	auto Rectangle::moveLeft()->void
	{
		translate(m_origin.add(vec3(-move, 0.0, 0.0)));
	}

	auto Rectangle::moveRight()->void
	{
		translate(m_origin.add(vec3(move, 0.0, 0.0)));
	}

	auto Rectangle::moveUp()->void
	{
		translate(m_origin.add(vec3(0.0, -move, 0.0)));
	}

	auto Rectangle::moveDown()->void
	{
		translate(m_origin.add(vec3(0.0, move, 0.0)));
	}

	auto Rectangle::translate(const vec3& translate) -> void
	{
		m_origin = translate;
	}

	auto Rectangle::resize(const vec3 & resize) -> void
	{

	}

	auto Rectangle::getWidth() -> float const
	{
		return m_dimension.x;
	}

	auto Rectangle::getHeight() -> float const
	{
		return m_dimension.y;
	}

	auto Rectangle::getOrigin() -> vec3 const
	{
		return m_origin;
	}

	auto Rectangle::getSprite() -> Sprite
	{
		return m_sprite;
	}

	auto Rectangle::rotate(const vec3 & translate, const vec3 & axis) -> void
	{
	}

	auto Rectangle::getType() const -> Type
	{
		return Type::RECTANGLE;
	}
}
