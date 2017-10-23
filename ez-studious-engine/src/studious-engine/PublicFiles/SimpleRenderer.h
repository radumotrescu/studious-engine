#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <map>

#include "Sprite.h"
#include "Rectangle.h"
#include "Shader.h"
#include "Light.h"


namespace SE
{
	struct LoopStruct
	{
		vec2 m_loopValue = vec2(0, 0);
		vec2 m_loopInterval = vec2(0, 0);
		LoopStruct(const vec2 value, const vec2 interval) :m_loopValue(value), m_loopInterval(interval)
		{
		}
		LoopStruct() {}
	};

	class SimpleRenderer
	{
	public:
		SimpleRenderer(const float screenWidth, const float screenHeight, const float depthLevel);
		~SimpleRenderer();
		auto addRectangleToDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto removeRectangleFromDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto setLightStatus(const bool enabled) const ->void;
		auto setLightPosition(const vec2 position) const ->void;
		auto setLightRadius(const float radius) const ->void;
		auto setLightIntensity(const float intensity) const ->void;
		auto draw() -> void;

	private:
		Shader m_shader = Shader();
		std::vector<std::shared_ptr<Rectangle>> m_drawVector;
		std::map<std::shared_ptr<Rectangle>, LoopStruct> scrollingMap;
	};
}
