#pragma once
#include <memory>

#include "SimpleRenderer.h"
#include "Window.h"
#include "LabelManager.h"

class Game
{
public:
	Game() = default;
	~Game() = default;

	virtual auto update() ->void = 0;
	virtual auto start() ->void = 0;
	virtual auto init() ->void;
	virtual auto run() ->void;
	virtual auto onTick() ->void;

protected:
	std::shared_ptr<SE::Window> m_window;
	std::shared_ptr<SE::SimpleRenderer> m_renderer;

	double currentTime;
	double t;
	double accumulator;
	static const double FPS;
};

