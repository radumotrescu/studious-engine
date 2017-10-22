#pragma once
#include <memory>
#include "Rectangle.h"
#include"SimpleRenderer.h"
#include "Utils.h"


class Ball {
public:
	Ball(SE::SimpleRenderer* renderer, float velocityX = 0.5f, float velocityY = 0.5f);
	~Ball() {};
	auto getRectangle() -> std::shared_ptr<SE::Rectangle>;
	auto move() ->void;
	auto onCollisionWithPad(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle>  pad) ->void;
	auto onCollisionWithBrick(std::shared_ptr<SE::Rectangle>  ball, std::shared_ptr<SE::Rectangle>  brick) ->void;

private:

	float m_velocityX;
	float m_velocityY;
	SE::SimpleRenderer* m_renderer;
	std::shared_ptr<SE::Rectangle> m_ball;
	static const float LEFT_MOVING_LIMIT;
	static const float RIGHT_MOVING_LIMIT;
};
