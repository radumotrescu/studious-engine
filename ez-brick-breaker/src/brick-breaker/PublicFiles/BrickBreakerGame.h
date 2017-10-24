#pragma once

#include <vector>
#include <memory>
#include <stack>

#include "Ball.h"
#include "Pad.h"
#include "Brick.h"
#include "Shader.h"
#include "Sprite.h"
#include "InputManager.h"
#include "CollisionChecker.h"
#include "Rectangle.h"
#include "Utils.h"
#include "CollisionManager.h"
#include "Game.h"
#include "Heart.h"
#include "SoundManager.h"
#include "LabelManager.h"
#include "Score.h"

using namespace SE;

class BrickBreakerGame : public Game
{
	public:

	BrickBreakerGame() = default;
	~BrickBreakerGame() = default;
	auto start() ->void override;
	auto init()->void override;

private:
	auto addBricksToRenderer() ->void;
	auto connectKeySignalsToPadMovement() const ->void;
	auto connectBehaviorOnCollision()->void;
	auto update() ->void override;
	auto onBallOutOfScope() -> void;

	CollisionChecker m_app;
	std::shared_ptr<SE::LabelManager> m_labelManager;
	std::shared_ptr<Score> m_scoreLabel;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<Pad> m_pad;
	std::stack <std::shared_ptr<Heart>> m_hearts;
	std::vector<Brick> m_bricks;
	static const int BRICK_WIDTH;
	static const int SPACE_BETWEEN_BRICKS;
};