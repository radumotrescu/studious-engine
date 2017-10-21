#include "Light.h"

namespace SE {

	 vec2 Light::m_position = vec2(0, 0);
	 bool Light::m_enabled = false;

	Light::Light()
	{
	}

	Light::~Light()
	{
	}

	auto Light::getPosition() -> const vec2
	{
		return m_position;
	}

		auto Light::getEnabled() -> const bool
	{
		return m_enabled;
	}

	auto Light::setPosition(const vec2 position) -> void
	{
		m_position = position;
	}

	auto Light::setEnabled(const bool enabled) -> void
	{
		m_enabled = enabled;
	}

}