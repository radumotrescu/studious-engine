#include "BrickBreakerGame.h"

const int BrickBreakerGame::BRICK_WIDTH = 15;
const int BrickBreakerGame::SPACE_BETWEEN_BRICKS = 5;

auto BrickBreakerGame::start() ->void
{
	init();
	addBricksToRenderer();
	connectKeySignalsToPadMovement();
	connectBehaviorOnCollision();
	run();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto BrickBreakerGame::init() -> void
{
	Game::init();
	m_ball = std::make_shared<Ball>(m_renderer.get(), 10, 5);
	m_pad = std::make_shared<Pad>(m_renderer.get());

	auto starsTexture = Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\stars.png");
	auto background = std::make_shared<SE::Rectangle>(SE::vec3(0, 0, 0), SE::vec2(200, 200), SE::vec3(1, 1, 1), starsTexture, 0);
	background->setScrollingSpeed(SE::vec2(0, -0.3));
	m_renderer->addRectangleToDrawCall(background);
}

auto BrickBreakerGame::addBricksToRenderer()->void
{
	const int  minRowIndexOnRow1 = 0;
	const int  minRowIndexOnRow2 = 1;
	const int  minRowIndexOnRow3 = 2;

	const int maxBrickIndexOnRow1 = 10;
	const int maxRowIndexOnRow2 = 9;
	const int maxRowIndexOnRow3 = 8;

	Texture brickTexture1("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\brick_1.png");
	Texture brickTexture2("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\brick_2.png");
	//Texture brickTexture3("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\brick_3.png");

	for (int i = minRowIndexOnRow1; i < maxBrickIndexOnRow1; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec3(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 20, 0), vec2(BRICK_WIDTH, 10), vec3(1.0f, 1.0f, 1.0f), brickTexture1));
	}
	for (int i = minRowIndexOnRow2; i < maxRowIndexOnRow2; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec3(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 30, 0), vec2(BRICK_WIDTH, 10), vec3(1.0f, 1.0f, 1.0f), brickTexture2));
	}

	for (int i = minRowIndexOnRow3; i < maxRowIndexOnRow3; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec3(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 40, 0), vec2(BRICK_WIDTH, 10), vec3(1.0f, 1.0f, 1.0f), brickTexture1));
	}
}

auto BrickBreakerGame::connectKeySignalsToPadMovement() ->void
{
	InputManager::getInstance().init(m_window->getWindow());
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveRight, m_pad.get()), GLFW_KEY_D);
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveLeft, m_pad.get()), GLFW_KEY_A);
}

auto BrickBreakerGame::connectBehaviorOnCollision() -> void
{
	SE::CollisionManager::addCollisionalEntities(m_ball->getRectangle(), m_pad->getRectangle(), std::bind(&Ball::onCollisionWithPad, m_ball.get(), std::placeholders::_1, std::placeholders::_2));
	for (auto& brick : m_bricks)
	{
		SE::CollisionManager::addCollisionalEntities(m_ball->getRectangle(), brick.getRectangle(), std::bind(&Brick::onCollisionWithBall, &brick, std::placeholders::_1, std::placeholders::_2));
	}
}

auto BrickBreakerGame::update() -> void
{
	m_ball->move();
	SE::CollisionManager::checkCollisions();
}


