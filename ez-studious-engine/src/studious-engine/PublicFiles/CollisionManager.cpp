#include <list>
#include <tuple>

#include "CollisionManager.h"


namespace SE
{
	std::list<std::tuple<std::shared_ptr<Rectangle>, std::shared_ptr<Rectangle>, std::function<void(std::shared_ptr<Rectangle> ,std::shared_ptr<Rectangle> )>>> CollisionManager::m_collisionalEntities;
	CollisionChecker CollisionManager::m_app;

	auto CollisionManager::getInstance()-> CollisionManager&
	{
		static CollisionManager collisionManager;

		return collisionManager;
	}

	auto CollisionManager::addCollisionalEntities(std::shared_ptr<Rectangle> collidedObject, std::shared_ptr<Rectangle> objectToColide, std::function<void(std::shared_ptr<Rectangle>, std::shared_ptr<Rectangle>)> func) -> void
	{
		m_collisionalEntities.push_back(std::make_tuple(std::move(collidedObject), std::move(objectToColide), func));
	}

	auto CollisionManager::checkCollisions() -> void
	{
		for(auto &&tupleEntities : m_collisionalEntities)
		{
			if(m_app.isCollided(std::get<0>(tupleEntities).get(), std::get<1>(tupleEntities).get()))
			{ 
				auto test = std::get<0>(tupleEntities).get();
				std::get<2>(tupleEntities)(std::get<0>(tupleEntities), std::get<1>(tupleEntities));
			}
		}
	}
}
