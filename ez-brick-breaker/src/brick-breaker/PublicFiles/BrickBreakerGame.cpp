#include "BrickBreakerGame.h"

const int BrickBreakerGame::BRICK_WIDTH = 15;
const int BrickBreakerGame::SPACE_BETWEEN_BRICKS = 5;

BrickBreakerGame::BrickBreakerGame()
{
	// window && glClearColor first!
	m_window = std::make_unique<SE::Window>("Test", 600, 800);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//renderer depeds on window context
	m_renderer = std::make_unique<SimpleRenderer>();
	m_ball = std::make_unique<Ball>(m_renderer.get(), 10, 5);
	m_pad = std::make_unique<Pad>(m_renderer.get());
}

auto BrickBreakerGame::start() ->void
{
	addBricksToRenderer();
	connectKeySignalsToPadMovement();
	update();
}

auto BrickBreakerGame::addBricksToRenderer()->void
{
	const int  minRowIndexOnRow1 = 0;
	const int  minRowIndexOnRow2 = 1;
	const int  minRowIndexOnRow3 = 2;

	const int maxBrickIndexOnRow1 = 10;
	const int maxRowIndexOnRow2 = 9;
	const int maxRowIndexOnRow3 = 8;

	for (int i = minRowIndexOnRow1; i < maxBrickIndexOnRow1; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec3(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 20, 0), vec2(BRICK_WIDTH, 4), vec3(0.0f, 1.0f, 0.0f)));
	}
	for (int i = minRowIndexOnRow2; i < maxRowIndexOnRow2; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec3(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 30, 0), vec2(BRICK_WIDTH, 4), vec3(1.0f, 0.0f, 1.0f)));
	}

	for (int i = minRowIndexOnRow3; i < maxRowIndexOnRow3; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec3(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 40, 0), vec2(BRICK_WIDTH, 4), vec3(0.0f, 0.0f, 1.0f)));
	}
}

auto BrickBreakerGame::connectKeySignalsToPadMovement() ->void
{
	InputManager::getInstance().init(m_window->getWindow());
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveRight, m_pad.get()), GLFW_KEY_D);
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveLeft, m_pad.get()), GLFW_KEY_A);
}


auto BrickBreakerGame::update() ->void
{

	double t = 0.0;
	double dt = 1 / 120.0;

	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	while (!m_window->closed())
	{

		m_window->clear();

		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;


		while (accumulator >= dt)
		{
			// ---------------

			m_ball->move();
			if (m_app.isCollided(m_ball->getRectangle(), m_pad->getRectangle()))
			{
				m_ball->onCollisionWithPad();
				std::cout << "P";
			}
			for (auto& brick : m_bricks)
			{
				SE::Rectangle * brickEntity = brick.getRectangle();
				if (m_app.isCollided(brickEntity, m_ball->getRectangle()))
				{
					m_ball->onCollisionWithBrick();
					brick.onCollisionWithBall();
					std::cout << "B";
				}
			}

			// ---------------
			accumulator -= dt;
			t += dt;
		}

		m_renderer->draw();

		accumulator += frameTime;

		m_window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}