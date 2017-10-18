#include "Pad.h"

const float Pad::LEFT_MOVING_LIMIT = 2.0f;
const float Pad::RIGHT_MOVING_LIMIT = 200.0f;

Pad::Pad(SE::SimpleRenderer* renderer, float velocityX, float velocityY)
	:m_renderer(renderer)
	, m_velocityX(velocityX)
	, m_velocityY(velocityY)
	, m_pad(std::make_shared<SE::Rectangle>(SE::vec3(5.0f, 190.0f, 0.0f), SE::vec2(20, 5), SE::vec3(1, 1, 1), Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\platform_1.png"), 0))
{
	renderer->addToDrawCall(m_pad);
}



auto Pad::getRectangle() ->SE::Rectangle *
{
	return m_pad.get();
}

auto Pad::moveRight() ->void
{
	auto origin = m_pad->getOrigin();

	if (SE::Utils::inRange(origin.x + 2, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - m_pad->getWidth()))
	{

		origin = origin.add(SE::vec3(m_velocityX*5.0f, m_velocityY*0.0f, 0.0f));
		m_pad->translate(origin);
	}

}

auto Pad::moveLeft() ->void
{
	auto origin = m_pad->getOrigin();

	if (SE::Utils::inRange(origin.x - 2, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - m_pad->getWidth()))
	{
		origin = origin.add(SE::vec3(-m_velocityX*5.0f, m_velocityY*0.0f, 0.0f));
		m_pad->translate(origin);
	}

}