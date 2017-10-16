#include "Brick.h"

Brick::Brick(SE::SimpleRenderer* renderer, SE::vec3 position, SE::vec2 size, SE::vec3 color)
	:renderer(renderer)
	, brick(std::make_shared<SE::Rectangle>(position, size, color, 0))
{
	renderer->addToDrawCall(brick);
}


auto Brick::getRectangle() ->SE::Rectangle*
{
	return brick.get();
}


auto Brick::onCollisionWithBall() ->void
{
	brick->translate(SE::vec3(1.0, 1.0, 0.0));
}