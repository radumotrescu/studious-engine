#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"
#include "Application.h"

#include <Rectangle.h>
#include <Utils.h>

#include <vector>
#include <chrono>

using namespace SE;

class Pad {
public:

	Pad(std::shared_ptr<SimpleRenderer> renderer, float velocityX = 0.5f, float velocityY = 0.5f)
		:renderer(renderer)
		, velocityX(velocityX)
		, velocityY(velocityY)
		, pad(std::make_shared<SE::Rectangle>(vec3(5.0f, 190.0f, 0.0f), vec2(20, 5), vec3(132.0f, 100.0f, 255.0f), 0))
	{
		renderer->addToDrawCall(pad);
	}
	virtual ~Pad() = default;

	SE::Rectangle * getRectangle()
	{
		return pad.get();
	}

	void moveRight()
	{
		auto origin = pad->getOrigin();

		if (SE::Utils::inRange(origin.x + 2, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - pad->getWidth()))
		{

			origin = origin.add(vec3(velocityX*5.0f, velocityY*0.0f, 0.0f));
			pad->translate(origin);
		}

	}

	void moveLeft()
	{
		auto origin = pad->getOrigin();

		if (SE::Utils::inRange(origin.x - 2, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - pad->getWidth()))
		{
			origin = origin.add(vec3(-velocityX*5.0f, velocityY*0.0f, 0.0f));
			pad->translate(origin);
		}

	}

private:

	float velocityX;
	float velocityY;
	std::shared_ptr<SimpleRenderer> renderer;
	std::shared_ptr<SE::Rectangle> pad;
	static const float LEFT_MOVING_LIMIT;
	static const float RIGHT_MOVING_LIMIT;

};
const float Pad::LEFT_MOVING_LIMIT = 2.0f;
const float Pad::RIGHT_MOVING_LIMIT = 200.0f;


class Ball {
public:
	Ball(std::shared_ptr<SimpleRenderer> renderer, float velocityX = 0.5f, float velocityY = 0.5f)
		: renderer(renderer)
		, velocityX(velocityX)
		, velocityY(velocityY)
		, ball(std::make_shared<SE::Rectangle>(vec3(5.0f, 40.0f, 1.0f), vec2(5, 5), vec3(255.0f, 0.0f, 0.0f), 0))
	{
		renderer->addToDrawCall(ball);
	}
	~Ball() = default;

	SE::Rectangle * getRectangle()
	{
		return ball.get();
	}

	void move()
	{
		auto origin = ball->getOrigin();
		if (SE::Utils::definitelyGreaterThan(origin.y, 230.0f))
		{
			throw std::string("Game OVER!");
		}
		if (SE::Utils::definitelyLessThan(origin.y, 2.0f))
		{
			velocityX = velocityX;
			velocityY = -velocityY;
		}
		if (!SE::Utils::inRange(origin.x, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - ball->getWidth()))
		{
			velocityX = -velocityX;
			velocityY = velocityY;
		}
		origin = origin.add(vec3(velocityX*0.1f, velocityY* 0.1f, 0.0f));
		ball->translate(origin);
	}
	void onCollisionWithPad()
	{
		velocityY = -velocityY;
		velocityX = velocityX;
	}

	void onCollisionWithBrick()
	{
		velocityY = -velocityY;
		velocityX = velocityX;
	}

private:

	float velocityX;
	float velocityY;
	std::shared_ptr<SimpleRenderer> renderer;
	std::shared_ptr<SE::Rectangle> ball;
	static const float LEFT_MOVING_LIMIT;
	static const float RIGHT_MOVING_LIMIT;

};

const float Ball::LEFT_MOVING_LIMIT = 2.0f;
const float Ball::RIGHT_MOVING_LIMIT = 200.0f;

class Brick {

public:
	Brick(std::shared_ptr<SimpleRenderer> renderer, vec3 position, vec2 size, vec3 color)
		:renderer(renderer)
		, brick(std::make_shared<SE::Rectangle>(position, size, color, 0))
	{
		renderer->addToDrawCall(brick);
	}

	~Brick() = default;

	SE::Rectangle * getRectangle()
	{
		return brick.get();
	}

	void onCollisionWithBall()
	{
		brick->translate(vec3(1.0, 1.0, 0.0));
	}

private:

	std::shared_ptr<SimpleRenderer> renderer;
	std::shared_ptr<SE::Rectangle> brick;
};


class Timer {
public:
	Timer() :
		m_beg(clock_::now())
	{
	}
	void reset()
	{
		m_beg = clock_::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(
			clock_::now() - m_beg).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> m_beg;
};


auto main() -> void
{
	auto window = std::make_unique<Window>("Test", 600, 800);

	//no color backround
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	std::shared_ptr<SimpleRenderer> ren = std::make_shared<SimpleRenderer>();
	Application app;

	//Rectangle(starting point, size, color)
	/*auto s1 = std::make_shared<SE::Rectangle>(vec3(3.0f, 4.0f, 0.0f), vec2(100, 100), vec3(0.0, 1.0, 0.0), 2);
	auto s2 = std::make_shared<SE::Rectangle>(vec3(50.0f, 100.0f, 0.0f), vec2(50, 50), vec3(1.0, 0.0, 1.0), 1);
	auto s3 = std::make_shared<SE::Rectangle>(vec3(25.0f, 33.0f, 0.0f), vec2(25, 25), vec3(0.0, 0.0, 1.0), 0);*/


	//auto s1 = std::make_shared<Sprite>(vec3(3.0f, 4.0f, 0.0f), vec2(10,10), vec3(0.0, 1.0, 0.0), 0);
	//auto s2 = std::make_shared<Sprite >(vec3(50.0f, 100.0f, 0.0f),vec2(50,50), vec3(1.0, 0.0, 1.0), 1);

	//InputManager::getInstance().init(window.get()->getWindow());
	//InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveLeft, s2.get()), GLFW_KEY_A);
	//InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveRight, s2.get()), GLFW_KEY_D);
	//InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveUp, s2.get()), GLFW_KEY_W);
	//InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveDown, s2.get()), GLFW_KEY_S);
	//or even

	//float inc = -2.0f;
	//auto funcPointer = static_cast<void(Sprite::*)(const vec3&)>(&Sprite::UpdateLocation);
	//InputManager::getInstance().registerSpriteAction(std::bind(funcPointer, s3.get(), s3->m_position.add(vec3(10, 10, 0.0f))), GLFW_KEY_S);

	//ren.addToDrawCall(s1);
	//ren.addToDrawCall(s2);
	//ren.addToDrawCall(s3);

	/*float inc = -0.1f;*/

	int brickWidth = 15;
	int spaceBetweenBricks = 5;
	std::vector<Brick> bricks;

	for (int i = 0; i < 10; i++)
		bricks.push_back(Brick(ren, vec3(i * brickWidth + i*spaceBetweenBricks, 20, 0), vec2(brickWidth, 4), vec3(0.0f, 1.0f, 0.0f)));

	for (int i = 1; i < 9; i++)
		bricks.push_back(Brick(ren, vec3(i * brickWidth + i*spaceBetweenBricks, 30, 0), vec2(brickWidth, 4), vec3(1.0f, 0.0f, 1.0f)));

	for (int i = 2; i < 8; i++)
		bricks.push_back(Brick(ren, vec3(i * brickWidth + i*spaceBetweenBricks, 40, 0), vec2(brickWidth, 4), vec3(0.0f, 0.0f, 1.0f)));


	Pad pad(ren);

	SE::Rectangle*padEntity = pad.getRectangle();

	InputManager::getInstance().init(window.get()->getWindow());
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveRight, &pad), GLFW_KEY_D);
	InputManager::getInstance().registerSpriteAction(std::bind(&Pad::moveLeft, &pad), GLFW_KEY_A);


	Ball ball(ren,10,5);
	SE::Rectangle* ballEntity = ball.getRectangle();


	double t = 0.0;
	double dt = 1 / 120.0;

	Timer timer;
	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	while (!window->closed())
	{

		window->clear();

		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;


		while (accumulator >= dt)
		{
			// ---------------

			ball.move();
			if (app.isCollided(ballEntity, padEntity))
			{
				ball.onCollisionWithPad();
				std::cout << "P";
			}
			for (auto& brick : bricks)
			{
				SE::Rectangle * brickEntity = brick.getRectangle();
				if (app.isCollided(brickEntity, ballEntity))
				{
					ball.onCollisionWithBrick();
					brick.onCollisionWithBall();
					std::cout << "B";
				}
			}

			// ---------------
			accumulator -= dt;
			t += dt;
		}

		ren->draw();

		accumulator += frameTime;

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


/*

TODO:
1. threaduri diferite pentru input si metoda de update: nu ia coliziunea in timp ce ia inputul
2. calcularea dinamica a widow-ului pentru limitarile bilei si pad-ului
3. contructorii de copiere si move in toate clasele, pentru a putea pasa ca paarametrii ai unei metode un shared_ptr

*/