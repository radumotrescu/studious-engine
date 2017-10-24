#include <Game.h>
#include <Rectangle.h>
#include <Texture.h>
#include <InputManager.h>
#include <CollisionManager.h>
#include <SoundManager.h>

#include <memory>

class MyGame : public Game {

public:
	MyGame()
	{
	}

	virtual auto update() -> void
	{
		SE::CollisionManager::checkCollisions();
		SoundManager::update();
	}
	virtual auto start() -> void
	{
		Game::init();
		SE::InputManager::init(Game::m_window->getWindow());
		SoundManager::init();

		texture1 = Texture("..//..//src//demo//PublicFiles//Textures//texture1.png");
		texture2 = Texture("..//..//src//demo//PublicFiles//Textures//texture2.png");

		rectangle1 = std::make_shared<SE::Rectangle>(SE::vec2(40, 40), SE::vec2(50, 50), texture1, 2);
		rectangle2 = std::make_shared<SE::Rectangle>(SE::vec2(150, 40), SE::vec2(50, 50), texture2, 3);

		sound1 = std::make_shared<Sound>("sunet1", "..//..//src//demo//PublicFiles//Sounds//cat_growl.wav");
		sound2 = std::make_shared<Sound>("sunet2", "..//..//src//demo//PublicFiles//Sounds//dog_bark.wav");

		Game::m_renderer->addRectangleToDrawCall(rectangle1);
		Game::m_renderer->addRectangleToDrawCall(rectangle2);

		SoundManager::add(sound1);
		SoundManager::add(sound2);

		glClearColor(1.0, 0.0, 0.0, 1.0);

		bindKeyToRectangles();
		bindRectangleToCollisionManager();
		Game::run();
	}

	auto moveRectangle1()->void
	{
		rectangle1->translate(SE::vec3(rectangle1->getOrigin().x + 1, rectangle1->getOrigin().y, rectangle1->getPriority()));
	}
	auto moveRectangle2()->void
	{
		rectangle2->translate(SE::vec3(rectangle2->getOrigin().x - 1, rectangle2->getOrigin().y, rectangle2->getPriority()));
	}

	auto bindKeyToRectangles()->void
	{
		SE::InputManager::registerSpriteAction(std::bind(&MyGame::moveRectangle1, this), GLFW_KEY_A);
		SE::InputManager::registerSpriteAction(std::bind(&MyGame::moveRectangle2, this), GLFW_KEY_D);
	}

	auto rectangleCollision(std::shared_ptr<SE::Rectangle> rectangle1, std::shared_ptr<SE::Rectangle> rectangle2)->void
	{
		static bool x = false;
		if (x == false)
		{
			SoundManager::get("sunet1")->play();
			SoundManager::get("sunet2")->play();
			x = true;
		}
	}

	auto bindRectangleToCollisionManager()->void
	{
		SE::CollisionManager::addCollisionalEntities(rectangle1, rectangle2, std::bind(&MyGame::rectangleCollision, this, std::placeholders::_1, std::placeholders::_2));
	}

	~MyGame()
	{
		SoundManager::clean();
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
	MyGame myGame;
	myGame.start();

	return 0;
}