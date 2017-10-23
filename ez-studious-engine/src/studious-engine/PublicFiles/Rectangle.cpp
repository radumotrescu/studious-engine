#include "Rectangle.h"


namespace SE {

	auto Rectangle::changePriority(const unsigned priority) -> void
	{
		m_priority = priority;
	}

	auto Rectangle::getTextureID()  -> GLuint
	{
		return m_sprite.m_texture.getID();
	}

	auto Rectangle::draw() -> void const
	{
		m_sprite.Draw();
	}

	Rectangle::Rectangle()
	{
	}

	Rectangle::Rectangle(const vec2 & position, const vec2 & dimension, const vec3 & color, const unsigned priority) 
		:m_origin(vec3(position.x,position.y,priority)), m_dimension(dimension), m_color(color), m_priority(priority)
	{
		Texture tex = Texture::getNullTexture();
		matrix = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
		colors = { 
			color.x, color.y, color.z, 1.0f,
			color.x, color.y, color.z, 1.0f,
			color.x, color.y, color.z, 1.0f,
			color.x, color.y, color.z, 1.0f 
		};
		m_sprite = Sprite(std::vector<GLfloat>(matrix.begin(), matrix.end()), std::vector<GLfloat>(colors.begin(), colors.end()), tex, std::vector<GLushort>(indexes.begin(), indexes.end()));

	}
	Rectangle::Rectangle(const vec2 & position, const vec2 & dimension, const Texture& texture, const unsigned priority)
		:m_origin(vec3(position.x,position.y,priority)), m_dimension(dimension), m_priority(priority)
	{
		matrix = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
		colors = {
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};
		m_sprite = Sprite(std::vector<GLfloat>(matrix.begin(), matrix.end()), std::vector<GLfloat>(colors.begin(), colors.end()),texture, std::vector<GLushort>(indexes.begin(), indexes.end()));
	}

	Rectangle::Rectangle(const vec2 & position, const vec2 & dimension, const vec3 & color, const Texture & texture, const unsigned priority)
		:m_origin(vec3(position.x,position.y,priority)), m_dimension(dimension), m_priority(priority)
	{
		matrix = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
		colors = { 
			color.x, color.y, color.z, 1.0f,
			color.x, color.y, color.z, 1.0f,
			color.x, color.y, color.z, 1.0f,
			color.x, color.y, color.z, 1.0f 
		};
		m_sprite = Sprite(std::vector<GLfloat>(matrix.begin(), matrix.end()), std::vector<GLfloat>(colors.begin(), colors.end()), texture, std::vector<GLushort>(indexes.begin(), indexes.end()));

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

	auto Rectangle::setScrollingSpeed(const vec2 scrollingSpeed) -> void
	{
		m_scrollingSpeed = scrollingSpeed;
	}

	auto Rectangle::translate(const vec3& translate) -> void
	{
		m_origin = translate;
	}

	auto Rectangle::resize(const vec3 & resize) -> void
	{

	}

	auto Rectangle::getWidth() const -> float const
	{
		return m_dimension.x;
	}

	auto Rectangle::getHeight() const -> float const
	{
		return m_dimension.y;
	}

	auto Rectangle::getOrigin() const -> vec3 const
	{
		return m_origin;
	}

	auto Rectangle::getScrollingSpeed() const -> vec2
	{
		return m_scrollingSpeed;
	}

	auto Rectangle::getAffectedByLighting() const -> bool
	{
		return m_affectedByLighting;
	}

	auto Rectangle::setAffectedByLighting(const bool affectedByLighting) -> void
	{
		m_affectedByLighting = affectedByLighting;
	}

	//auto Rectangle::getTextureId() -> unsigned int const
	//{
	//	return m_texture->getID();
	//}

	auto Rectangle::getSprite() const -> Sprite
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
