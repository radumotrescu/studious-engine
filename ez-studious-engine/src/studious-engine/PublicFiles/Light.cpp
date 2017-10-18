#include "Light.h"

namespace SE {
	Light::Light() 
	{
	}

	auto Light::addLight(const std::string & name, const vec3 & light) -> void
	{
		if (lightMap.find(name) != lightMap.end() || lightMap.size() < maxLights)
		{
			lightMap[name] = light;
		}
	}

	auto Light::getLightVector() const->std::array<float, 30>
	{
		unsigned mapSize = lightMap.size();
		std::array<float, 30> lightVector;
		unsigned index = 0;
		for (auto& light : lightMap)
		{
			lightVector[index++] = light.second.x;
			lightVector[index++] = light.second.y;
			lightVector[index++] = light.second.z;
		}
		while (index < maxLights*3)
		{
			lightVector[index++] = 0;
		}

		return lightVector;
	}

	auto Light::getPosition() const -> vec2
	{
		return m_position;
	}

	auto Light::getIntensity() const -> float
	{
		return m_intensity;
	}
}
