#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "Sprite.h"
#include "Shader.h"

class SimpleRenderer {

public:
	SimpleRenderer();
	~SimpleRenderer();
	auto addToDrawCall( std::shared_ptr<Sprite> sprite) ->void;
	auto draw() -> void;

private:
	const std::string fragPath = "basic.frag";
	const std::string vertPath = "basic.vert";
	Shader m_shader = Shader(vertPath, fragPath);
	std::vector<std::shared_ptr<Sprite>> m_drawVector;
};

