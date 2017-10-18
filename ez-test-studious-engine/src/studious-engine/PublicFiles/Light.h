#pragma once

#include "Vec2.h"
#include "Vec3.h"

#include <map>
#include <unordered_map>
#include <string>
#include <array>

namespace SE {
	class Light {

	public:
		Light();
		auto addLight(const std::string& name, const vec3& light)->void;
		auto getLightVector()const->std::array<float, 30>;

		auto getPosition()const->vec2;
		auto getIntensity()const->float;

	private:

		const unsigned maxLights = 10;
		std::unordered_map<std::string, vec3> lightMap;

		vec2 m_position;
		float m_intensity;

	};

}