#pragma once

#include "Rectangle.h"
#include "ICollisional.h"

namespace SE
{
	class TestCollisionalRectangle2 : public SE::Rectangle, virtual public SE::ICollisional
	{
	public:


		TestCollisionalRectangle2(const vec3& position, const vec2& dimension, const vec3& color, unsigned priority)
			: Rectangle(position, dimension, color, priority)
		{
		}

		TestCollisionalRectangle2(const vec3& position, const vec2& dimension, const Texture& texture, unsigned priority)
			: Rectangle(position, dimension, texture, priority)
		{
		}

		auto onCollision() -> void override;
	};
}