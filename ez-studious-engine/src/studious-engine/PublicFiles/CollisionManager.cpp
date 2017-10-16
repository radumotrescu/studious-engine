#include <list>

#include "CollisionManager.h"
#include <tuple>


namespace SE
{
	std::list<std::tuple<std::shared_ptr<ICollisional>, std::shared_ptr<ICollisional>>> CollisionManager::m_collisionalEntities;
	Application CollisionManager::m_app;

	auto CollisionManager::getInstance()-> CollisionManager&
	{
		static CollisionManager collisionManager;

		return collisionManager;
	}

	auto CollisionManager::addCollisionalEntities(std::shared_ptr<ICollisional> collidedObject, std::shared_ptr<ICollisional> objectToColide) -> void
	{
		m_collisionalEntities.push_back(std::make_tuple(std::move(collidedObject), std::move(objectToColide)));
	}

	auto CollisionManager::checkCollisions() -> void
	{
		for(auto &tupleEntities : m_collisionalEntities)
		{
			if(m_app.isCollided(std::get<0>(tupleEntities).get(), std::get<1>(tupleEntities).get()))
			{
				std::get<0>(tupleEntities).get()->onCollision();
				std::get<1>(tupleEntities).get()->onCollision();
			}
		}
	}
}
