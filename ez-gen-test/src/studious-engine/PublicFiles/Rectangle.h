#pragma once

#include "Entity.h"
#include "vec2.h"
#include "Sprite.h"

#include <glew.h>
#include <iostream>

namespace stud {

	class Rectangle : public IEntity {
	private:

		Sprite m_sprite;

		vec3 m_origin;
		vec2 m_dimension;
		unsigned m_priority;
		vec3 m_color;

		std::vector<GLfloat> matrix;
		std::vector<GLfloat> colors;

		std::vector<GLushort> indexes = {
			0,2,3,
			1,2,0
		};

	public:
		Rectangle(const vec3& position, const vec2& dimension, const vec3& color, const unsigned priority);

		auto changePointCoordinates(const vec3 & vertex)->void;
		auto changePriority(const unsigned priority) -> void;

		auto getPriority() const -> unsigned;

		virtual auto getType() const->Type override;

		virtual auto translate(const vec3& translate) -> void override;
		virtual auto resize(const vec3& resize) -> void override;
		//virtual auto rotate(const vec3 & rotate, const vec3& axis) -> void override;

		auto getWidth()->float const;
		auto getHeight()->float const;
		auto getOrigin()->vec3 const;

		auto getSprite()->Sprite;

		// Inherited via IEntity
		virtual auto rotate(const vec3 & translate, const vec3 & axis) -> void;

		auto moveLeft()->void;
		auto moveRight()->void;
		auto moveUp()->void;
		auto moveDown()->void;
	};
}