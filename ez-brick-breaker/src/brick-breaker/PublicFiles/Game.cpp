#include "Game.h"

const double Game::FPS = 1 / 120.0;

auto Game::init() -> void
{
	currentTime = glfwGetTime();
	t = 0.0;
	accumulator = 0.0;
	// window && glClearColor first!
	const float screenWidth = 600;
	const float screenHeight = 800;
	m_window = std::make_shared<SE::Window>("Test", screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//renderer depeds on window context
	m_renderer = std::make_shared<SE::SimpleRenderer>(200,200);


}

auto Game::run() -> void
{
	while (!m_window->closed())
	{
		m_window->clear();

		///////////////////////////////////////////////////////
		onTick();
		///////////////////////////////////////////////////////
		m_renderer->draw();
		m_window->update();
	}
}

auto Game::onTick() -> void
{
	double newTime = glfwGetTime();
	double frameTime = newTime - currentTime;
	currentTime = newTime;
	while (accumulator >= FPS)
	{
		// ---------------

		update();

		// ---------------
		accumulator -= FPS;
		t += FPS;
	}
	accumulator += frameTime;
}
