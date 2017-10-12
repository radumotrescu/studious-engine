#include "Label.h"
#include <glew.h>
#include <glut.h>

namespace SE
{
	Label::Label(const std::string& message, int pos, int pos1)
		: m_xPos(pos),
		m_yPos(pos1),
		m_message(message)
	{
	}

	auto Label::display() -> void
	{
		glColor3f(1.f, 0.3f, 0.f);
		glMatrixMode(GL_PROJECTION);
		double *matrix = new double[16];
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
		//glLoadIdentity();
		glOrtho(0, 800, 0, 600, -5, 5);
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(this->m_xPos, this->m_yPos);
		for (int index = 0; index < this->m_message.length(); index++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, this->m_message[index]);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(matrix);
		glMatrixMode(GL_MODELVIEW);
	}

	auto Label::setMessage(const std::string& message) -> void
	{
		this->m_message = message;
	}
}
