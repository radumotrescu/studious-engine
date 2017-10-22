#pragma once
#include <memory>

#include "SimpleRenderer.h"
#include "Window.h"
#include "LabelManager.h"
#include "Score.h"

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
	std::shared_ptr<SE::LabelManager> m_labelManager;
	std::shared_ptr<Score> m_scoreLabel;

	double currentTime;
	double t;
	double accumulator;
	static const double FPS;
};

