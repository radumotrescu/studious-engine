#pragma once

namespace SE
{
	class ICollisional
	{
	public:
		virtual auto onCollision() -> void = 0;

		virtual ~ICollisional() = default;
	};
}