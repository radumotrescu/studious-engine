#pragma once

#include "Rectangle.h"
#include "ICollisional.h"

namespace SE
{
	class TestCollisionalRectangle1 : public SE::Rectangle, virtual public SE::ICollisional
	{
	public:
		TestCollisionalRectangle1(const SE::vec3& position, const SE::vec2& dimension, const SE::vec3& color, unsigned priority)
			: Rectangle(position, dimension, color, priority)
		{
		}

		auto onCollision() -> void override;
	};
}