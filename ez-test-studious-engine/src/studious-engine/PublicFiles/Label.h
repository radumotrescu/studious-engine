#pragma once
#include <iostream>

namespace SE
{
	class Label
	{
	public:
		Label(const std::string& message, int pos, int pos1);
		auto display() -> void;
		auto setMessage(const std::string&) -> void;

	private:
		int m_xPos;
		int m_yPos;
		std::string m_message;
	};
}