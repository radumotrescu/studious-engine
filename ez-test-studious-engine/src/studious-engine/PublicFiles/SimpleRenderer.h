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
		SimpleRenderer();
		~SimpleRenderer();
		auto addRectangleToDrawCall(std::shared_ptr<Rectangle> sprite) ->void;
		auto addLightToDrawCall(std::shared_ptr<Light> light) -> void;
		auto draw() -> void;

	private:
		//const std::string fragPath = "basic.frag";
		//const std::string vertPath = "basic.vert";
		//Shader m_shader = Shader(vertPath, fragPath);
		Shader m_shader = Shader();
		std::vector<std::shared_ptr<Rectangle>> m_drawVector;
		std::shared_ptr<Light> m_light;
	};


}
