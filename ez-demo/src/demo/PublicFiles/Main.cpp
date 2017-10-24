#include <Game.h>
#include <Rectangle.h>
#include <Texture.h>
#include <InputManager.h>
#include <CollisionManager.h>
#include <SoundManager.h>

#include <memory>

class MyDemoGame : public Game {

public:
	MyDemoGame() = default;
	~MyDemoGame() = default;

	virtual auto start() -> void
	{
		Game::init();
		loadTextures();
		loadSounds();
		initDrawableSprite();

		glClearColor(1.0, 0.0, 0.0, 1.0);

		connectKeyPressedBehaviors();
		connectOnCollisionBehaviors();
		Game::run();
	}


private:
	virtual auto update() -> void
	{
		SE::CollisionManager::checkCollisions();
		SoundManager::update();
	}

	auto moveRectangle1()->void
	{
		auto newX = rectangle1->getOrigin().x + 1;
		auto newY = rectangle1->getOrigin().y;
		auto newPriority = rectangle1->getPriority();
		rectangle1->translate(SE::vec3(newX, newY, newPriority));
	}
	auto moveRectangle2()->void
	{
		auto newX = rectangle2->getOrigin().x - 1;
		auto newY = rectangle2->getOrigin().y;
		auto newPriority = rectangle2->getPriority();
		rectangle2->translate(SE::vec3(newX, newY, newPriority));
	}

	auto connectKeyPressedBehaviors()->void
	{
		SE::InputManager::init(Game::m_window->getWindow());
		SE::InputManager::registerSpriteAction(std::bind(&MyDemoGame::moveRectangle1, this), GLFW_KEY_A);
		SE::InputManager::registerSpriteAction(std::bind(&MyDemoGame::moveRectangle2, this), GLFW_KEY_D);
	}

	auto rectangleCollision(std::shared_ptr<SE::Rectangle> rectangle1, std::shared_ptr<SE::Rectangle> rectangle2)->void
	{
		static bool isFirstCollision = true;
		if (isFirstCollision)
		{
			SoundManager::get("sunet1")->play();
			SoundManager::get("sunet2")->play();
			isFirstCollision = false;
		}
	}

	auto connectOnCollisionBehaviors()->void
	{
		SE::CollisionManager::addCollisionalEntities(rectangle1, rectangle2, std::bind(&MyDemoGame::rectangleCollision, this, std::placeholders::_1, std::placeholders::_2));
	}

	auto loadTextures() ->void
	{
		texture1 = Texture("..//..//src//demo//PublicFiles//Textures//texture1.png");
		texture2 = Texture("..//..//src//demo//PublicFiles//Textures//texture2.png");
	}

	auto initDrawableSprite() ->void
	{
		rectangle1 = std::make_shared<SE::Rectangle>(SE::vec2(40, 40), SE::vec2(50, 50), texture1, 2);
		rectangle2 = std::make_shared<SE::Rectangle>(SE::vec2(150, 40), SE::vec2(50, 50), texture2, 2);
		Game::m_renderer->addRectangleToDrawCall(rectangle1);
		Game::m_renderer->addRectangleToDrawCall(rectangle2);
	}

	auto loadSounds() ->void
	{
		SoundManager::init();
		sound1 = std::make_shared<Sound>("sunet1", "..//..//src//demo//PublicFiles//Sounds//cat_growl.wav");
		sound2 = std::make_shared<Sound>("sunet2", "..//..//src//demo//PublicFiles//Sounds//dog_bark.wav");
		
		SoundManager::add(sound1);
		SoundManager::add(sound2);
	}

private:
	Texture texture1;
	Texture texture2;

	std::shared_ptr<SE::Rectangle> rectangle1;
	std::shared_ptr<SE::Rectangle> rectangle2;

	std::shared_ptr<Sound> sound1;
	std::shared_ptr<Sound> sound2;
};

int main()
{
	MyDemoGame myGame;
	myGame.start();
	return 0;
}