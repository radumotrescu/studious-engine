#include "Label.h"

namespace SE
{
	Label::Label(const std::string& message, const int& pos, const int& pos1, const int& size)
		: m_xPos(pos),
		m_yPos(pos1),
		m_size(size)
	{
		gltInit();
		this->m_GLTtext = gltCreateText();
		gltSetText(this->m_GLTtext, message.c_str());
		this->m_colors = vec3(1.0, 1.0, 1.0);
	}		

	auto Label::display() const -> void
	{
		gltColor(this->m_colors.x, this->m_colors.y, this->m_colors.z, this->m_size);
		gltDrawText2D(this->m_GLTtext, m_xPos, m_yPos, m_size);
	}

	auto Label::setMessage(const std::string& message) const -> void
	{
		gltSetText(this->m_GLTtext, message.c_str());
	}

	auto Label::setPosition(const int& xPos, const int& yPos) -> void
	{
		this->m_xPos = xPos;
		this->m_yPos = yPos;
	}

	auto Label::setColor(const vec3& colors) -> void
	{
		this->m_colors = colors;
	}
}
