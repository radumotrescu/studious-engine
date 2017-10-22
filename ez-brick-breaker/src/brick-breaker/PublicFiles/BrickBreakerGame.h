#pragma once

#include "Ball.h"
#include "Pad.h"
#include "Brick.h"
#include "Shader.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Application.h"
#include "Rectangle.h"
#include "Utils.h"
#include "CollisionManager.h"
#include <vector>
#include <memory>
#include "Game.h"
using namespace SE;

class BrickBreakerGame : public Game
{

public:

	BrickBreakerGame() = default;
	~BrickBreakerGame() = default;
	auto start() ->void;
	auto init()->void;

private:
	auto addBricksToRenderer() ->void;
	auto connectKeySignalsToPadMovement() const ->void;
	auto connectBehaviorOnCollision()->void;
	auto update() ->void;

private:
	Application m_app;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<Pad> m_pad;
	std::vector<Brick> m_bricks;
	static const int BRICK_WIDTH;
	static const int SPACE_BETWEEN_BRICKS;

};