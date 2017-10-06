#pragma once

#include "Sprite.h"
#include "Shader.h"

#include <vector>
#include <algorithm>
#include <string>

class SimpleRenderer {
private:
	const std::string fragPath = "basic.frag";
	const std::string vertPath = "basic.vert";
	Shader m_shader = Shader(vertPath, fragPath);
	std::vector<Sprite> m_drawVector;

public:
	SimpleRenderer();
	~SimpleRenderer();

	auto addToDrawCall(const Sprite& sprite) ->void;
	auto draw() -> void;
};

