#include "Heart.h"

Heart::Heart(SE::SimpleRenderer* renderer, SE::vec3 pos)
	: m_renderer(renderer),
	  m_heart(std::make_shared<SE::Rectangle>(pos, SE::vec2(10, 10), SE::vec3(1.f, 1.f, 1.f), Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\heart.png"), 5))
{
	renderer->addRectangleToDrawCall(m_heart);
}

Heart::~Heart()
{
	m_renderer->removeRectangleFromDrawCall(m_heart);
}
