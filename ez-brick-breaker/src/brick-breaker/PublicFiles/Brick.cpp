#include "Brick.h"

Brick::Brick(SE::SimpleRenderer* renderer, SE::vec3 position, SE::vec2 size, SE::vec3 color, const Texture& texture)
	:renderer(renderer)
	, brick(std::make_shared<SE::Rectangle>(position, size, color, texture, 0))
{
	renderer->addRectangleToDrawCall(brick);
}


auto Brick::getRectangle() ->std::shared_ptr<SE::Rectangle>
{
	return brick;
}


auto Brick::onCollisionWithBall(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle> brick) ->void
{
	//brick->translate(SE::vec3(1.0, 1.0, 0.0));
	renderer->removeRectangleFromDrawCall(brick);
}
