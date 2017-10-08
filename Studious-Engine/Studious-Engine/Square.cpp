#include "Square.h"



Square::Square()
{
	this->m_xCoordinate = 100;
	this->m_yCoordinate = 100;
	this->m_size = 100;
}

auto Square::display() -> void
{
	glBegin(GL_POINTS);
	glVertex2f(-.1f, .1f);
	glEnd();
}


Square::~Square()
{
}
