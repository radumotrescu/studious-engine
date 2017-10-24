#pragma once
#include <memory>

#include "Rectangle.h"
#include "SimpleRenderer.h"
#include "Utils.h"
#include "SoundManager.h"


class Brick
{
public:
	Brick(SE::SimpleRenderer* renderer, SE::vec2 position, SE::vec2 size, SE::vec3 color, const Texture& texture);
	~Brick() {};
	auto getRectangle() const->std::shared_ptr<SE::Rectangle>;
	auto onCollisionWithBall(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle> brick) const ->void;

private:
	SE::SimpleRenderer* renderer;
	std::shared_ptr<SE::Rectangle> brick;
};

