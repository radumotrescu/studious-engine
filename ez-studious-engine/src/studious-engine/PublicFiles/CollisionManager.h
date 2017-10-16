#pragma once

#include <list>
#include <memory>

#include "Application.h"

namespace SE
{
	class CollisionManager
	{
	public:
		static auto getInstance()->CollisionManager&;
		static auto addCollisionalEntities(std::shared_ptr<ICollisional> collidedObject,
		                            std::shared_ptr<ICollisional> objectToColide) -> void;


		static auto checkCollisions() -> void;

	private:
		static std::list<std::tuple<std::shared_ptr<ICollisional>, std::shared_ptr<ICollisional>>> m_collisionalEntities;
		static Application m_app;
	};
}
