#pragma once
#include <memory>
#include "Rectangle.h"
#include"SimpleRenderer.h"
#include "Utils.h"


class Brick {

public:
	Brick(SE::SimpleRenderer* renderer, SE::vec3 position, SE::vec2 size, SE::vec3 color, const Texture& texture);
	~Brick() {};
	auto getRectangle()->SE::Rectangle*;
	auto onCollisionWithBall() ->void;

private:

	SE::SimpleRenderer* renderer;
	std::shared_ptr<SE::Rectangle> brick;
};

