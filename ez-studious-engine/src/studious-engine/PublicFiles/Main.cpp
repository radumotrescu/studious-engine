#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"
#include "Application.h"
#include "Rectangle.h"
#include "glut.h"

auto main() -> void
{
	auto window = std::make_unique<SE::Window>("Test", 600, 800);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SE::SimpleRenderer ren;

	auto s1 = std::make_shared<SE::Rectangle>(SE::vec3(3.0f, 4.0f, 0.0f), SE::vec2(100, 100), SE::vec3(0.0, 1.0, 0.0), 2);
	auto s2 = std::make_shared<SE::Rectangle>(SE::vec3(50.0f, 100.0f, 0.0f), SE::vec2(50, 50), SE::vec3(1.0, 0.0, 1.0), 1);
	auto s3 = std::make_shared<SE::Rectangle>(SE::vec3(25.0f, 33.0f, 0.0f), SE::vec2(25, 25), SE::vec3(0.0, 0.0, 1.0), 0);

	SE::Application app;
	//auto s1 = std::make_shared<Sprite>(vec3(3.0f, 4.0f, 0.0f), vec2(10,10), vec3(0.0, 1.0, 0.0), 0);
	//auto s2 = std::make_shared<Sprite >(vec3(50.0f, 100.0f, 0.0f),vec2(50,50), vec3(1.0, 0.0, 1.0), 1);

	SE::InputManager::getInstance().init(window.get()->getWindow());
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveLeft, s2.get()), GLFW_KEY_A);
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveRight, s2.get()), GLFW_KEY_D);
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveUp, s2.get()), GLFW_KEY_W);
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveDown, s2.get()), GLFW_KEY_S);
	//or even

	float inc = -2.0f;
	//auto funcPointer = static_cast<void(Sprite::*)(const vec3&)>(&Sprite::UpdateLocation);
	//InputManager::getInstance().registerSpriteAction(std::bind(funcPointer, s3.get(), s3->m_position.add(vec3(10, 10, 0.0f))), GLFW_KEY_S);

	ren.addToDrawCall(s1);
	ren.addToDrawCall(s2);
	ren.addToDrawCall(s3);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);
	//float inc = -0.1f;

	while (!window->closed())
	{
		window->clear();
		auto og = s1->getOrigin();
		//s1->translate(og.add(vec3(-inc*0.1f, -inc* 0.1f, 0.0f)));
		if (s1->getOrigin().y > 200 || s1->getOrigin().y < 0)
			inc = -inc;
		std::cout << app.isCollided(s1.get(), s2.get());
		ren.draw();
		//std::cout << " ---------- " << s1->getOrigin().x << " --------------- " << std::endl;

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
