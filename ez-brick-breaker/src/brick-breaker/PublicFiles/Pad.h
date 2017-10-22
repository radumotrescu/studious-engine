#pragma once
#include <memory>
#include "Rectangle.h"
#include"SimpleRenderer.h"
#include "Utils.h"


class Pad {
public:

	Pad(SE::SimpleRenderer* renderer, float velocityX = 0.5f, float velocityY = 0.5f);
	~Pad() {};
	auto getRectangle()->std::shared_ptr<SE::Rectangle >;
	auto moveRight() ->void;
	auto moveLeft() ->void;
	auto setPosition(SE::vec3 position) -> void;

private:

	float m_velocityX;
	float m_velocityY;
	SE::SimpleRenderer* m_renderer;
	std::shared_ptr<SE::Rectangle> m_pad;
	static const float LEFT_MOVING_LIMIT;
	static const float RIGHT_MOVING_LIMIT;
};
