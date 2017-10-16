#include "Rectangle.h"


namespace SE {

	//auto Rectangle::changePointCoordinates(const vec3 & position) -> void
	//{
	//	m_origin = position;
	//}

	auto Rectangle::changePriority(const unsigned priority) -> void
	{
		m_priority = priority;
	}

	void Rectangle::setTextureCoordDefaults()
	{
		m_textureCoord.push_back(vec2(0, 1));
		m_textureCoord.push_back(vec2(0, 0));
		m_textureCoord.push_back(vec2(1, 0));
		m_textureCoord.push_back(vec2(1, 1));
	}

	auto Rectangle::setTextureVector() -> void
	{
		textures = {
			m_textureCoord[0].x, m_textureCoord[0].y,
			m_textureCoord[1].x, m_textureCoord[1].y,
			m_textureCoord[2].x, m_textureCoord[2].y,
			m_textureCoord[3].x, m_textureCoord[3].y
		};
	}

	Rectangle::Rectangle()
	{
		setTextureCoordDefaults();
	}
	Rectangle::Rectangle(const vec3 & position, const vec2 & dimension, const vec3 & color, const unsigned priority) :m_origin(position), m_dimension(dimension), m_color(color), m_priority(priority)
	{
		glActiveTexture(GL_TEXTURE0);
		m_texture = std::make_shared<Texture>("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\nothing.png");
		m_texture->bind();

		m_origin.z = priority;
		matrix = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
		colors = { color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f,color.x,color.y,color.z,1.0f };

		setTextureCoordDefaults();
		setTextureVector();

		m_sprite = Sprite(std::vector<GLfloat>(matrix.begin(), matrix.end()), std::vector<GLfloat>(colors.begin(), colors.end()), std::vector<GLfloat>(textures.begin(), textures.end()), std::vector<GLushort>(indexes.begin(), indexes.end()));
	}
	Rectangle::Rectangle(const vec3 & position, const vec2 & dimension, const Texture& texture, const unsigned priority)
		:m_origin(position), m_dimension(dimension), m_priority(priority)
	{
		glActiveTexture(GL_TEXTURE1);
		m_texture = std::make_shared<Texture>(texture);
		m_texture->bind();
		matrix = { 0,0,0,dimension.y,dimension.x,dimension.y,dimension.x,0 };
		colors = {
			1, 1, 1, 1,
			1, 1, 1, 1,
			1, 1, 1, 1,
			1, 1, 1, 1
		};
		setTextureCoordDefaults();
		setTextureVector();
		//create a sprite with the textureCoord vector
		m_sprite = Sprite(std::vector<GLfloat>(matrix.begin(), matrix.end()), std::vector<GLfloat>(colors.begin(), colors.end()), std::vector<GLfloat>(textures.begin(), textures.end()), std::vector<GLushort>(indexes.begin(), indexes.end()));
	}
	
	auto Rectangle::display() -> void
	{
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

	auto Rectangle::getTextureId() -> unsigned int const
	{
		return m_texture->getID();
	}

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
