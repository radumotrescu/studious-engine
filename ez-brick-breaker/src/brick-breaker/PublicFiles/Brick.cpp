#include "Brick.h"

Brick::Brick(SE::SimpleRenderer* renderer, SE::vec3 position, SE::vec2 size, SE::vec3 color, const Texture& texture)
	:renderer(renderer)
	, brick(std::make_shared<SE::Rectangle>(position, size, color, texture, 3))
{
	renderer->addRectangleToDrawCall(brick);
}


auto Brick::getRectangle() const -> std::shared_ptr<SE::Rectangle>
{
	return brick;
}


auto Brick::onCollisionWithBall(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle> brick) const -> void
{
	brick->translate(SE::vec3(500.0, 500.0, 0.0));
	renderer->removeRectangleFromDrawCall(brick);
}
