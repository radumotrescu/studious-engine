#include "Light.h"

namespace SE {

	 vec2 Light::m_position = vec2(0, 0);
	 bool Light::m_enabled = false;
	 float Light::m_intensity = 0.0f;
	 float Light::m_radius = 0.0f;

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

	auto Light::getRadius() -> const float
	{
		return m_radius;
	}

	auto Light::getIntensity() -> const float
	{
		return m_intensity;
	}

	auto Light::setPosition(const vec2 position) -> void
	{
		m_position = position;
	}

	auto Light::setEnabled(const bool enabled) -> void
	{
		m_enabled = enabled;
	}

	auto Light::setRadius(const float radius) -> void
	{
		m_radius = radius;
	}

	auto Light::setIntensity(const float intensity) -> void
	{
		m_intensity = intensity;
	}

}