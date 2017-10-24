#pragma once

#include <iostream>
#include <glew.h>

#include "gltext.h"
#include "Vec3.h"

namespace SE
{
	class Label
	{
	public:
		Label() = default;
		Label(const std::string& message, const int& pos, const int& pos1, const int& size);
		auto display() const -> void;
		auto setMessage(const std::string&) const -> void;
		auto setPosition(const int& xPos, const int& yPos) -> void;
		auto setColor(const vec3& colors) -> void;

	private:
		int m_xPos;
		int m_yPos;
		int m_size;

		GLTtext* m_GLTtext;
		vec3 m_colors;
	};
}
