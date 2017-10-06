#include "SimpleRenderer.h"


SimpleRenderer::SimpleRenderer()
{
	m_shader.enable();
}


SimpleRenderer::~SimpleRenderer()
{
	m_shader.disable();
}

bool compareSpritePriority(Sprite s1, Sprite s2)
{
	return s1.getPriority() > s2.getPriority();
}

auto SimpleRenderer::addToDrawCall(const Sprite & sprite) -> void
{
	m_drawVector.push_back(sprite);
	std::sort(m_drawVector.begin(), m_drawVector.end(),compareSpritePriority);
}

auto SimpleRenderer::draw() -> void
{
	for (auto& sprite : m_drawVector)
	{
		sprite.Draw();
	}
}
