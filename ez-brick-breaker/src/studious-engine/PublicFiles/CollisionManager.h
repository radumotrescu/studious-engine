#pragma once

#include <list>
#include <memory>

#include "CollisionChecker.h"
#include <functional>

namespace SE
{
	class CollisionManager
	{
	public:
		static auto getInstance()->CollisionManager&;
		static auto addCollisionalEntities(std::shared_ptr<Rectangle> collidedObject,
			std::shared_ptr<Rectangle> objectToColide,
			std::function<void(std::shared_ptr<Rectangle>, std::shared_ptr<Rectangle>)>) -> void;


		static auto checkCollisions() -> void;

	private:
		static std::list<std::tuple<std::shared_ptr<Rectangle>, std::shared_ptr<Rectangle>, std::function<void(std::shared_ptr<Rectangle>, std::shared_ptr<Rectangle>)>>> m_collisionalEntities;
		static CollisionChecker m_app;
	};
}
