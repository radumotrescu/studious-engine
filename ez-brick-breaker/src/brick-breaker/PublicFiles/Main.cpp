#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"
#include "Application.h"

#include <Rectangle.h>

using namespace SE;
float EPSILON = std::numeric_limits<float>::epsilon();


auto approximatelyEqual(float a, float b, float epsilon = EPSILON)->bool
{
	return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto essentiallyEqual(float a, float b, float epsilon = EPSILON)->bool
{
	return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto definitelyGreaterThan(float a, float b, float epsilon = EPSILON)->bool
{
	return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto definitelyLessThan(float a, float b, float epsilon = EPSILON)->bool
{
	return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto rangeIntersection(float minRange1, float maxRange1, float minRange2, float maxRange2) -> bool
{
	auto min1 = (std::min)(minRange1, maxRange1);
	auto min2 = (std::min)(minRange2, maxRange2);
	auto max1 = (std::max)(minRange1, maxRange1);
	auto max2 = (std::max)(minRange2, maxRange2);

	auto minLessOrEqualToValue1 = essentiallyEqual(min1, min2) || definitelyLessThan(min1, min2);
	auto value1LessOrEqualToMax = essentiallyEqual(min2, max1) || definitelyLessThan(min2, max1);

	auto minLessOrEqualToValue2 = essentiallyEqual(min1, max2) || definitelyLessThan(min1, max2);
	auto value2LessOrEqualToMax = essentiallyEqual(max2, max1) || definitelyLessThan(max2, max1);

	return  (minLessOrEqualToValue1 && value1LessOrEqualToMax) || (minLessOrEqualToValue2 && value2LessOrEqualToMax);
}

auto inRange(float value, float minRange, float maxRange) -> bool
{
	auto min = (std::min)(minRange, maxRange);
	auto max = (std::max)(minRange, maxRange);
	auto minLessOrEqualToValue = essentiallyEqual(min, value) || definitelyLessThan(min, value);
	auto valueLessOrEqualToMax = essentiallyEqual(value, max) || definitelyLessThan(value, max);

	return minLessOrEqualToValue && valueLessOrEqualToMax;
}
class Pad
{
public:

	Pad(SimpleRenderer* renderer, float velocityX = 0.5f, float velocityY = 0.5f)
		:renderer(renderer)
		, velocityX(velocityX)
		, velocityY(velocityY)
		, pad(std::make_shared<SE::Rectangle>(vec3(5.0f, 10.0f, 0.0f), vec2(20, 5), vec3(132.0f, 100.0f, 255.0f), 0))
	{
		renderer->addToDrawCall(pad);
	}
	virtual ~Pad() = default;

	SE::Rectangle * getRectangle()
	{
		return pad.get();
	}

	void move()
	{
		auto origin = pad->getOrigin();
		//std::cout << origin.x << std::endl;
		if (!inRange(origin.x, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - pad->getWidth()))
		{
			velocityX = -velocityX;
		}

		//origin = origin.add(vec3(velocityX*0.1f, velocityY*0.0f, 0.0f));
		pad->translate(origin);
	}

	void stopMoving()
	{

	}



private:

	float velocityX;
	float velocityY;
	SimpleRenderer* renderer;
	std::shared_ptr<SE::Rectangle> pad;
	static const float LEFT_MOVING_LIMIT;
	static const float RIGHT_MOVING_LIMIT;




};
const float Pad::LEFT_MOVING_LIMIT = 2.0f;
const float Pad::RIGHT_MOVING_LIMIT = 200.0f;


class Ball
{
public:
	Ball(SimpleRenderer* renderer, float velocityX = 0.5f, float velocityY = 0.5f)
		: renderer(renderer)
		, velocityX(velocityX)
		, velocityY(velocityY)
		, ball(std::make_shared<SE::Rectangle>(vec3(5.0f, 10.0f, 1.0f), vec2(5, 5), vec3(255.0f, 0.0f, 0.0f), 0))
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
		//std::cout << origin.x << std::endl;
		if (!inRange(origin.x, LEFT_MOVING_LIMIT, RIGHT_MOVING_LIMIT - ball->getWidth()))
		{
			velocityX = -velocityX;
			velocityY = -velocityY;
		}

		//origin = origin.add(vec3(velocityX*0.1f, velocityY* 0.1f, 0.0f));
		ball->translate(origin);
	}
	void onCollision()
	{

	}

private:

	float velocityX;
	float velocityY;
	SimpleRenderer* renderer;
	std::shared_ptr<SE::Rectangle> ball;
	static const float LEFT_MOVING_LIMIT;
	static const float RIGHT_MOVING_LIMIT;

};

const float Ball::LEFT_MOVING_LIMIT = 2.0f;
const float Ball::RIGHT_MOVING_LIMIT = 200.0f;
auto main() -> void
{
	auto window = std::make_unique<Window>("Test", 600, 800);

	//no color backround
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SimpleRenderer ren;


	//Rectangle(starting point, size, color)
	auto s1 = std::make_shared<SE::Rectangle>(vec3(3.0f, 4.0f, 0.0f), vec2(100, 100), vec3(0.0, 1.0, 0.0), 2);
	auto s2 = std::make_shared<SE::Rectangle>(vec3(50.0f, 100.0f, 0.0f), vec2(50, 50), vec3(1.0, 0.0, 1.0), 1);
	auto s3 = std::make_shared<SE::Rectangle>(vec3(25.0f, 33.0f, 0.0f), vec2(25, 25), vec3(0.0, 0.0, 1.0), 0);

	Application app;
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

	ren.addToDrawCall(s1);
	ren.addToDrawCall(s2);
	ren.addToDrawCall(s3);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);
	float inc = -0.1f;
	Pad pad(&ren);
	Ball ball(&ren);
	while (!window->closed())
	{
		window->clear();
		pad.move();
		ball.move();
		SE::Rectangle* a = ball.getRectangle();
		SE::Rectangle*b = pad.getRectangle();
		auto is = app.isCollided(a, b);
		if (is)
		{
			std::cout << 1 << std::endl;
		}
		/*auto og = s1->getOrigin();
		s1->translate(og.add(vec3(-inc*0.1f, -inc* 0.1f, 0.0f)));*/
		/*if (s1->getOrigin().y > 200 || s1->getOrigin().y < 0)
			inc = -inc;*/
			//std::cout << app.isCollided(s1.get(), s2.get());
		ren.draw();
		//std::cout << " ---------- " << s1->getOrigin().x << " --------------- " << std::endl;

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
