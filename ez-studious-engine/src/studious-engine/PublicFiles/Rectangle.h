#pragma once

#include "IEntity.h"
#include "vec2.h"
#include "Sprite.h"

#include <glew.h>
#include <iostream>


namespace SE {
	class Rectangle : virtual public IEntity {
	private:

		Sprite m_sprite;

		vec3 m_origin;
		vec2 m_dimension;
		unsigned m_priority;
		vec3 m_color;

		std::array<GLfloat, 8> matrix;
		std::array<GLfloat, 16> colors;

		std::array<GLushort, 6> indexes = {
			0,2,3,
			1,2,0
		};

	public:
		Rectangle(const vec3& position, const vec2& dimension, const vec3& color, const unsigned priority);

		auto display() -> void override;
		//auto changePointCoordinates(const vec3 & vertex)->void;
		auto changePriority(const unsigned priority) -> void;

		auto getPriority() const -> unsigned;

		auto getType() const->Type override;

		auto translate(const vec3& translate) -> void override;
		auto resize(const vec3& resize) -> void override;

		auto getWidth() const ->float const;
		auto getHeight() const ->float const;
		auto getOrigin() const ->vec3 const;

		auto getSprite() const ->Sprite;

		// Inherited via IEntity
		virtual auto rotate(const vec3 & translate, const vec3 & axis) -> void;

		auto moveLeft()->void;
		auto moveRight()->void;
		auto moveUp()->void;
		auto moveDown()->void;

	};
}