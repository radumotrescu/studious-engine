#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "Sprite.h"
#include "Rectangle.h"
#include "Shader.h"
#include "Light.h"

namespace SE {
	class SimpleRenderer {

	public:
		SimpleRenderer::SimpleRenderer(const float screenWidth, const float screenHeight);
		~SimpleRenderer();
		auto addRectangleToDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto removeRectangleFromDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto setLightStatus(const bool enabled)->void;
		auto setLightPosition(const vec2 position)->void;
		auto draw() -> void;

	private:
		//const std::string fragPath = "basic.frag";
		//const std::string vertPath = "basic.vert";
		//Shader m_shader = Shader(vertPath, fragPath);

		Shader m_shader = Shader();
		std::vector<std::shared_ptr<Rectangle>> m_drawVector;
	};


}
