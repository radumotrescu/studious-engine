#include <Game.h>
#include <Rectangle.h>
#include <Texture.h>
#include <InputManager.h>
#include <CollisionManager.h>
#include <SoundManager.h>

#include <memory>

class MyGame : public SE::Game {

public:
	MyGame()
	{
	}

	virtual auto update() -> void
	{
		SE::CollisionManager::checkCollisions();
		SE::SoundManager::update();
	}
	virtual auto start() -> void
	{
		Game::init();
		SE::InputManager::init(Game::m_window->getWindow());
		SE::SoundManager::init();

		texture1 = SE::Texture("..//..//src//demo//PublicFiles//Textures//texture1.png");
		texture2 = SE::Texture("..//..//src//demo//PublicFiles//Textures//texture2.png");

		rectangle1 = std::make_shared<SE::Rectangle>(SE::vec2(40, 40), SE::vec2(50, 50), texture1, 2);
		rectangle2 = std::make_shared<SE::Rectangle>(SE::vec2(150, 40), SE::vec2(50, 50), texture2, 3);

		sound1 = std::make_shared<SE::Sound>("sunet1", "..//..//src//demo//PublicFiles//Sounds//cat_growl.wav");
		sound2 = std::make_shared<SE::Sound>("sunet2", "..//..//src//demo//PublicFiles//Sounds//dog_bark.wav");

		Game::m_renderer->addRectangleToDrawCall(rectangle1);
		Game::m_renderer->addRectangleToDrawCall(rectangle2);

		SE::SoundManager::add(sound1);
		SE::SoundManager::add(sound2);

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
			SE::SoundManager::get("sunet1")->play();
			SE::SoundManager::get("sunet2")->play();
			x = true;
		}
	}

	auto bindRectangleToCollisionManager()->void
	{
<<<<<<< HEAD
		//const auto th = std::make_shared<MyGame>(this);
		//aux x;
		SE::CollisionManager::addCollisionalEntities(rectangle1, rectangle2, std::bind(&MyGame::rectangleCollision ,this, std::placeholders::_1, std::placeholders::_2));
=======
		SE::CollisionManager::addCollisionalEntities(rectangle1, rectangle2, std::bind(&MyGame::rectangleCollision, this, std::placeholders::_1, std::placeholders::_2));
>>>>>>> c68e477470da945b06df93f63c2ec8c697193f17
	}

	~MyGame()
	{
		SE::SoundManager::clean();
	}



private:
	SE::Texture texture1;
	SE::Texture texture2;

	std::shared_ptr<SE::Rectangle> rectangle1;
	std::shared_ptr<SE::Rectangle> rectangle2;

	std::shared_ptr<SE::Sound> sound1;
	std::shared_ptr<SE::Sound> sound2;
};



int main()
{
	MyGame myGame;
	myGame.start();

	return 0;
}