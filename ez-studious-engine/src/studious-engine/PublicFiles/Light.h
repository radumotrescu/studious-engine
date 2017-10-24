#pragma once

#include "Vec2.h"

namespace SE
{
	class Light
	{
	public:

		static auto getPosition()->const vec2;
		static auto getEnabled()->const bool;
		static auto getRadius()->const float;
		static auto getIntensity()->const float;

		static auto setPosition(const vec2 position)->void;
		static auto setEnabled(const bool enabled)->void;
		static auto setRadius(const float radius)->void;
		static auto setIntensity(const float intensity)->void;

	private:
		Light();
		~Light();
		static vec2 m_position;
		static bool m_enabled;
		static float m_radius;
		static float m_intensity;
	};
}