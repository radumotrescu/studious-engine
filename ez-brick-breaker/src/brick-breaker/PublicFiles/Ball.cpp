#include "Ball.h"


const float Ball::LEFT_MOVING_LIMIT = 2.0f;
const float Ball::RIGHT_MOVING_LIMIT = 200.0f;

Ball::Ball(SE::SimpleRenderer* renderer, float velocityX, float velocityY)
	: m_renderer(renderer)
	, m_velocityX(velocityX)
	, m_velocityY(velocityY)
	, m_ball(std::make_shared<SE::Rectangle>(SE::vec3(5.0f, 40.0f, 1.0f), SE::vec2(5, 5), SE::vec3(255.0f, 0.0f, 0.0f), 0))
{
	renderer->addToDrawCall(m_ball);
}

auto Ball::getRectangle() ->SE::Rectangle*
{
	return m_ball.get();
}

auto Ball::move() ->void
{
	auto origin = m_ball->getOrigin();
	if (SE::Utils::definitelyGreaterThan(origin.y, 230.0f))
	{
		throw std::string("Game OVER!");
	}
	if (SE::Utils::definitelyLessThan(origin.y, 2.0f))
	{
		m_velocityX = m_velocityX;
		m_velocityY = -m_velocityY;
	}
	if (!SE::Utils::inRange(origin.x, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - m_ball->getWidth()))
	{
		m_velocityX = -m_velocityX;
		m_velocityY = m_velocityY;
	}
	origin = origin.add(SE::vec3(m_velocityX*0.1f, m_velocityY* 0.1f, 0.0f));
	m_ball->translate(origin);
}


auto Ball::onCollisionWithPad() ->void
{
	m_velocityY = -m_velocityY;
	m_velocityX = m_velocityX;
}

auto Ball::onCollisionWithBrick() ->void
{
	m_velocityY = -m_velocityY;
	m_velocityX = m_velocityX;
}