#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <map>

#include "Sprite.h"
#include "Rectangle.h"
#include "Shader.h"
#include "Light.h"


namespace SE {
	class SimpleRenderer {

	public:
		SimpleRenderer(const float screenWidth, const float screenHeight, const float depthLevel);
		~SimpleRenderer();
		auto addRectangleToDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto removeRectangleFromDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto setLightStatus(const bool enabled)->void;
		auto setLightPosition(const vec2 position)->void;
		auto setLightRadius(const float radius)->void;
		auto setLightIntensity(const float intensity)->void;
		auto draw() -> void;

	private:
		//const std::string fragPath = "basic.frag";
		//const std::string vertPath = "basic.vert";
		//Shader m_shader = Shader(vertPath, fragPath);

		Shader m_shader = Shader();
		std::vector<std::shared_ptr<Rectangle>> m_drawVector;

		struct LoopStruct {
		public:
			vec2 m_loopValue = vec2(0, 0);
			vec2 m_loopInterval = vec2(0, 0);
			LoopStruct(const vec2 value, const vec2 interval) :m_loopValue(value), m_loopInterval(interval)
			{
			}
			LoopStruct() {}

		};
		std::map<std::shared_ptr<Rectangle>, LoopStruct> scrollingMap;
	};


}
