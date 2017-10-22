#pragma once

#include "Vec2.h"

namespace SE {

	class Light {

	public:

		static auto getPosition()->const vec2;
		static auto getEnabled()->const bool;

		static auto setPosition(const vec2 position)->void;
		static auto setEnabled(const bool enabled)->void;

	private:
		Light();
		~Light();
		static vec2 m_position;
		static bool m_enabled;
	};
}