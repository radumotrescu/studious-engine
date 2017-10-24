#include "Pad.h"

const float Pad::LEFT_MOVING_LIMIT = 2.0f;
const float Pad::RIGHT_MOVING_LIMIT = 200.0f;

Pad::Pad(SE::SimpleRenderer* renderer, const float velocityX, const float velocityY)
	:m_renderer(renderer)
	, m_velocityX(velocityX)
	, m_velocityY(velocityY)
	, m_pad(std::make_shared<SE::Rectangle>(SE::vec2(90.0f, 190.0f), SE::vec2(20, 5), SE::vec3(1, 1, 1), SE::Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\platform_1.png"), 1))
{
	renderer->addRectangleToDrawCall(m_pad);
}



auto Pad::getRectangle() const ->std::shared_ptr<SE::Rectangle>
{
	return m_pad;
}

auto Pad::moveRight() const ->void
{
	auto origin = m_pad->getOrigin();

	if (SE::Utils::inRange(origin.x + 2, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - m_pad->getWidth()))
	{

		origin = origin.add(SE::vec3(m_velocityX*5.0f, m_velocityY*0.0f, 0.0f));
		m_pad->translate(origin);
	}
}

auto Pad::moveLeft() const ->void
{
	auto origin = m_pad->getOrigin();

	if (SE::Utils::inRange(origin.x - 2, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - m_pad->getWidth()))
	{
		origin = origin.add(SE::vec3(-m_velocityX*5.0f, m_velocityY*0.0f, 0.0f));
		m_pad->translate(origin);
	}
}

auto Pad::setPosition(const SE::vec2 position) const -> void
{
	this->m_pad->translate(SE::vec3(position.x,position.y,m_pad->getPriority()));
}
