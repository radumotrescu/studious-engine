#include <Game.h>
#include <Rectangle.h>
#include <Texture.h>
#include <InputManager.h>
#include <CollisionManager.h>
#include <SoundManager.h>

#include <memory>

using namespace SE;

//                      "..//..//src//demo//PublicFiles//Textures//texture1.png"
//                      "sunet1", "..//..//src//demo//PublicFiles//Sounds//sound1.wav"

class MyDemoGameStruct : public Game
{
public:
	MyDemoGameStruct() = default;
	~MyDemoGameStruct() = default;
	virtual auto start() -> void
	{
		Game::init();
		initDrawableSprite();
		Game::m_window->setTitle("My Demo Game!");
		


		Game::run();
	}
private:
	virtual auto update() -> void
	{
	}

	auto initDrawableSprite() ->void
	{
		auto coordinatesForRectangle1 = SE::vec2(40, 40);
		auto sizeForRectangle1 = SE::vec2(50, 50);
		auto colorForRectangle1 = vec3(1.0f, 0.0f, 0.0f);
		auto drawPriorityForRectangle1 = 2;
		rectangle1 = std::make_shared<SE::Rectangle>(coordinatesForRectangle1, sizeForRectangle1, colorForRectangle1, drawPriorityForRectangle1);

		auto coordinatesForRectangle2 = SE::vec2(120, 40);
		auto sizeForRectangle2 = SE::vec2(50, 50);
		auto colorForRectangle2 = vec3(0.0f, 1.0f, 0.0f);
		auto drawPriorityForRectangle2 = 3;
		rectangle2 = std::make_shared<SE::Rectangle>(coordinatesForRectangle2, sizeForRectangle2, colorForRectangle2, drawPriorityForRectangle2);

		Game::m_renderer->addRectangleToDrawCall(rectangle1);
		Game::m_renderer->addRectangleToDrawCall(rectangle2);
	}


	auto onCollision(std::shared_ptr<Rectangle>&r1, std::shared_ptr<Rectangle>&r2) ->void
	{
		static bool isFirstCollision = true;
		if (isFirstCollision)
		{
			std::cout << "Poc";
			isFirstCollision = false;
		}
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

private:

	std::shared_ptr<SE::Rectangle> rectangle1;
	std::shared_ptr<SE::Rectangle> rectangle2;
};



int main()
{
	

	MyDemoGameStruct game;
	game.start();
	return 0;
}