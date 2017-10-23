#include "Ball.h"
#include <corecrt_math_defines.h>

const float Ball::LEFT_MOVING_LIMIT = 2.0f;
const float Ball::RIGHT_MOVING_LIMIT = 200.0f;

Ball::Ball(SE::SimpleRenderer* renderer, const float velocityX, const float velocityY, const float speed)
	: m_renderer(renderer)
	, m_velocityX(velocityX)
	, m_velocityY(velocityY)
	, m_speed(speed)
	, m_ball(std::make_shared<SE::Rectangle>(SE::vec2(98.0f, 184.0f), SE::vec2(5, 5), SE::vec3(1.0f, 1.0f, 1.0f), Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\meteor_1.png"), 2))
{
	renderer->addRectangleToDrawCall(m_ball);
	this->m_isMoving = true;
}

auto Ball::getRectangle() const -> std::shared_ptr<SE::Rectangle>
{
	return m_ball;
}

auto Ball::move() ->void
{
	m_renderer->setLightPosition(SE::vec2(m_ball->getOrigin().x + m_ball->getWidth() / 2, m_ball->getOrigin().y + m_ball->getHeight() / 2));
	if (!this->m_isMoving)
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
}


auto Ball::onCollisionWithPad(std::shared_ptr<SE::Rectangle>& ball, std::shared_ptr<SE::Rectangle>& pad) ->void
{
	static bool isFirstCollisionWithPad = true;
	static auto lastCollisionTime = std::chrono::system_clock::now();

	const auto currentCollisionTime = std::chrono::system_clock::now();
	const std::chrono::duration<float> passedTime = currentCollisionTime - lastCollisionTime;
	const std::chrono::duration<float> latency(0.3f);

	if (passedTime >= latency || isFirstCollisionWithPad)
	{
		std::cout << "collision with pad counted" << std::endl;

		const auto relativeIntersection = (pad->getOrigin().x + ((pad->getWidth()) / 2)) - m_ball->getOrigin().x;
		const auto ratio = relativeIntersection / (pad->getWidth() / 2);
		const auto maxAngle = 5 * M_PI / 12; //75 grade
		const auto repulsionAngle = ratio * maxAngle;
		m_velocityX = (-std::sin(repulsionAngle));

		m_velocityY = (-std::cos(repulsionAngle));

		lastCollisionTime = currentCollisionTime;
		isFirstCollisionWithPad = false;

		SoundManager::get("hitWithPad")->play();
	}
	else
	{
		std::cout << "collision with pad NOT counted" << std::endl;
	}
}

auto Ball::onCollisionWithBrick(std::shared_ptr<SE::Rectangle>& ball, std::shared_ptr<SE::Rectangle>&  brick) ->void
{
	const auto relativeIntersection = (brick->getOrigin().x + ((brick->getWidth()) / 2)) - m_ball->getOrigin().x;
	const auto ratio = relativeIntersection / (brick->getWidth() / 2);
	const auto maxAngle = 5 * M_PI / 12; //75 grade
	const auto repulsionAngle = ratio * maxAngle;
	m_velocityX = (-std::sin(repulsionAngle));
	m_velocityY = (std::cos(repulsionAngle));

}

auto Ball::toggleIsMoving() -> void
{
	this->m_isMoving = !this->m_isMoving;
}

auto Ball::setPosition(const SE::vec2 position) const -> void
{
	this->m_ball.get()->translate(SE::vec3(position.x,position.y,m_ball.get()->getPriority()));
}
