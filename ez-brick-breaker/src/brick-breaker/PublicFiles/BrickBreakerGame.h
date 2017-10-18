#pragma once

#include "Ball.h"
#include "Pad.h"
#include "Brick.h"
#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"
#include "Application.h"
#include "Rectangle.h"
#include "Utils.h"
#include "CollisionManager.h"
#include <vector>
#include <memory>

using namespace SE;

class BrickBreakerGame
{

public:

	BrickBreakerGame();
	~BrickBreakerGame() = default;
	auto start() ->void;

private:
	auto addBricksToRenderer() ->void;
	auto connectKeySignalsToPadMovement() ->void;
	auto connectBehaviorOnCollision()->void;
	auto update() ->void;

private:

	std::shared_ptr<SE::Window> m_window;
	std::shared_ptr<SimpleRenderer> m_renderer;
	Application m_app;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<Pad> m_pad;
	std::vector<Brick> m_bricks;
	static const int BRICK_WIDTH;
	static const int SPACE_BETWEEN_BRICKS;
};