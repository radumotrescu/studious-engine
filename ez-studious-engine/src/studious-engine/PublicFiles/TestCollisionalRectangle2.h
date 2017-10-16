#pragma once

#include "Rectangle.h"
#include "ICollisional.h"

namespace SE
{
	class TestCollisionalRectangle2 : public SE::Rectangle, virtual public SE::ICollisional
	{
	public:
		TestCollisionalRectangle2(const SE::vec3& position, const SE::vec2& dimension, const SE::vec3& color, unsigned priority)
			: Rectangle(position, dimension, color, priority)
		{
		}

		auto onCollision() -> void override;
	};
}