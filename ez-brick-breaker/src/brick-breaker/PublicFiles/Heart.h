#pragma once

#include <Rectangle.h>
#include <SimpleRenderer.h>

class Heart
{
public:
	Heart(SE::SimpleRenderer* renderer, SE::vec2 pos);
	~Heart();

private:
	SE::SimpleRenderer* m_renderer;
	std::shared_ptr<SE::Rectangle> m_heart;
};
