#include "Ball.h"


const float Ball::LEFT_MOVING_LIMIT = 2.0f;
const float Ball::RIGHT_MOVING_LIMIT = 200.0f;

Ball::Ball(SE::SimpleRenderer* renderer, float velocityX, float velocityY, float speed)
	: m_renderer(renderer)
	, m_velocityX(velocityX)
	, m_velocityY(velocityY)
	, m_speed(speed)
	, m_ball(std::make_shared<SE::Rectangle>(SE::vec3(5.0f, 40.0f, 1.0f), SE::vec2(5, 5), SE::vec3(1.0f, 1.0f, 1.0f), Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\meteor_1.png"), 0))
{
	renderer->addRectangleToDrawCall(m_ball);
}

auto Ball::getRectangle() ->std::shared_ptr<SE::Rectangle>
{
	return m_ball;
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
	origin = origin.add(SE::vec3(m_velocityX*m_speed, m_velocityY*m_speed, 0.0f));
	m_ball->translate(origin);
}


auto Ball::onCollisionWithPad(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle> pad) ->void
{
	static bool isFirstCollisionWithPad = true;
	static auto lastCollisionTime = std::chrono::system_clock::now();

	auto currentCollisionTime = std::chrono::system_clock::now();
	std::chrono::duration<float> passedTime = currentCollisionTime - lastCollisionTime;
	std::chrono::duration<float> latency(0.3f);

	if (passedTime >= latency || isFirstCollisionWithPad)
	{
		std::cout << "collision with pad counted" << std::endl;

		auto relativeIntersection = (pad->getOrigin().x + ((pad->getWidth()) / 2)) - m_ball->getOrigin().x;
		auto ratio = relativeIntersection / (pad->getWidth() / 2);
		auto maxAngle = 5 * M_PI / 12; //75 grade
		auto repulsionAngle = ratio * maxAngle;
		m_velocityX = (-std::sin(repulsionAngle));
			
		m_velocityY = (-std::cos(repulsionAngle));

		lastCollisionTime = currentCollisionTime;
		isFirstCollisionWithPad = false;
	}
	else
	{
		std::cout << "collision with pad NOT counted" << std::endl;
	}

}

auto Ball::onCollisionWithBrick(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle>  brick) ->void
{
	auto relativeIntersection = (brick->getOrigin().x + ((brick->getWidth()) / 2)) - m_ball->getOrigin().x;
	auto ratio = relativeIntersection / (brick->getWidth() / 2);
	auto maxAngle = 5 * M_PI / 12; //75 grade
	auto repulsionAngle = ratio * maxAngle;
	m_velocityX = (-std::sin(repulsionAngle));
	m_velocityY = (std::cos(repulsionAngle));
	
}
