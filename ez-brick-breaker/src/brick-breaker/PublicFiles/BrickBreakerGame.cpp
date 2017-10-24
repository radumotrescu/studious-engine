#include "BrickBreakerGame.h"


const int BrickBreakerGame::BRICK_WIDTH = 15;
const int BrickBreakerGame::SPACE_BETWEEN_BRICKS = 5;

auto BrickBreakerGame::start() ->void
{
	init();
	addBricksToRenderer();
	connectKeySignalsToPadMovement();
	connectBehaviorOnCollision();
	SoundManager::get("background")->loop();
	run();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto BrickBreakerGame::init() -> void
{
	Game::init();
	m_ball = std::make_shared<Ball>(m_renderer.get());
	m_pad = std::make_shared<Pad>(m_renderer.get());
	// init labels
	SE::LabelManager::init();
	SE::LabelManager::setIsDisplayingFps(true);
	m_scoreLabel = std::make_shared<Score>();
	auto label = m_scoreLabel.get()->getLabel();
	label.setColor(SE::vec3(0.5f, 0.6f, 0.01f));
	SE::LabelManager::addLabel(label);

	m_hearts.push(std::make_shared<Heart>(m_renderer.get(), SE::vec2(185.f, 5.f)));
	m_hearts.push(std::make_shared<Heart>(m_renderer.get(), SE::vec2(175.f, 5.f)));
	m_hearts.push(std::make_shared<Heart>(m_renderer.get(), SE::vec2(165.f, 5.f)));
	auto starsTexture = Texture("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\stars.png");
	auto background = std::make_shared<SE::Rectangle>(SE::vec2(0, 0), SE::vec2(200, 200), SE::vec3(1, 1, 1), starsTexture, 0);

	background->setScrollingSpeed(SE::vec2(0, -0.3));
	m_renderer->addRectangleToDrawCall(background);
	m_renderer->setLightStatus(true);
	m_renderer->setLightRadius(100);
	m_renderer->setLightIntensity(0.4);

	SoundManager::init();

	const auto hitWithPadSound = std::make_shared<Sound>("hitWithPad", "..\\..\\src\\studious-engine\\PublicFiles\\Sounds\\hit2.wav");
	const auto hithWithBrickSound = std::make_shared<Sound>("hitWithBrick", "..\\..\\src\\studious-engine\\PublicFiles\\Sounds\\hit.wav");
	const auto backgroundSound = std::make_shared<Sound>("background", "..\\..\\src\\studious-engine\\PublicFiles\\Sounds\\acdc.mp3");


	SoundManager::add(hitWithPadSound);
	SoundManager::add(hithWithBrickSound);
	SoundManager::add(backgroundSound);
}

auto BrickBreakerGame::addBricksToRenderer()->void
{
	const int  minRowIndexOnRow1 = 0;
	const int  minRowIndexOnRow2 = 1;
	const int  minRowIndexOnRow3 = 2;

	const int maxBrickIndexOnRow1 = 10;
	const int maxRowIndexOnRow2 = 9;
	const int maxRowIndexOnRow3 = 8;

	const Texture brickTexture1("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\brick_1.png");
	const Texture brickTexture2("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\brick_2.png");

	for (int i = minRowIndexOnRow1; i < maxBrickIndexOnRow1; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec2(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 20), vec2(BRICK_WIDTH, 10), vec3(1.0f, 1.0f, 1.0f), brickTexture1));
	}
	for (int i = minRowIndexOnRow2; i < maxRowIndexOnRow2; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec2(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 30), vec2(BRICK_WIDTH, 10), vec3(1.0f, 1.0f, 1.0f), brickTexture2));
	}

	for (int i = minRowIndexOnRow3; i < maxRowIndexOnRow3; i++)
	{
		m_bricks.push_back(Brick(m_renderer.get(), vec2(i * BRICK_WIDTH + i*SPACE_BETWEEN_BRICKS, 40), vec2(BRICK_WIDTH, 10), vec3(1.0f, 1.0f, 1.0f), brickTexture1));
	}
}

auto BrickBreakerGame::connectKeySignalsToPadMovement() const -> void
{
	InputManager::getInstance().init(m_window->getWindow());
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveRight, m_pad.get()), GLFW_KEY_D);
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveLeft, m_pad.get()), GLFW_KEY_A);
	InputManager::getInstance().registerSpriteAction(std::bind(&Ball::toggleIsMoving, m_ball.get()), GLFW_KEY_SPACE);
}

auto BrickBreakerGame::connectBehaviorOnCollision() -> void
{
	SE::CollisionManager::addCollisionalEntities(m_ball->getRectangle(), m_pad->getRectangle(), std::bind(&Ball::onCollisionWithPad, m_ball, std::placeholders::_1, std::placeholders::_2));
	for (auto& brick : m_bricks)
	{
		SE::CollisionManager::addCollisionalEntities(m_ball->getRectangle(), brick.getRectangle(), std::bind(&Ball::onCollisionWithBrick, m_ball, std::placeholders::_1, std::placeholders::_2));
		SE::CollisionManager::addCollisionalEntities(m_ball->getRectangle(), brick.getRectangle(), std::bind(&Score::increaseScore, this->m_scoreLabel.get(), std::placeholders::_1, std::placeholders::_2));
		SE::CollisionManager::addCollisionalEntities(m_ball->getRectangle(), brick.getRectangle(), std::bind(&Brick::onCollisionWithBall, &brick, std::placeholders::_1, std::placeholders::_2));
	}
}

auto BrickBreakerGame::update() -> void
{
	try
	{
		m_ball->move();
	}
	catch (std::string ex)
	{
		onBallOutOfScope();
	}
	SE::CollisionManager::checkCollisions();
}

auto BrickBreakerGame::onBallOutOfScope() -> void
{
	m_ball->toggleIsMoving();
	m_ball->setPosition(vec2(98.0f, 184.0f));
	m_pad->setPosition(vec2(90.0f, 190.0f));

	m_hearts.pop();

	if (m_hearts.size() < 1)
	{
		auto label = SE::Label("Game over", 270, 270, 3);
		label.setColor(vec3(1.f, 0.f, 0.f));
		SE::LabelManager::addLabel(label);

		SE::InputManager::removeSpriteAction(GLFW_KEY_SPACE);
		SE::InputManager::removeSpriteAction(GLFW_KEY_A);
		SE::InputManager::removeSpriteAction(GLFW_KEY_D);
	}
}


