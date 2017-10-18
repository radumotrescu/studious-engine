#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"
#include "Application.h"
#include "Rectangle.h"
#include "glut.h"
#include "LabelManager.h"
#include "CollisionManager.h"
#include "ft2build.h"
#include "Light.h"
#include "Vec3.h"

#include FT_FREETYPE_H

static const int WINDOW_WIDTH = 600;
static const int WINDOW_HEIGHT = 800;

#if 1

namespace SE
{
	class test
	{
	public:
		void method(std::shared_ptr<Rectangle> t1, std::shared_ptr<Rectangle> t2)
		{
			t1->moveLeft();
		}
	};
}

auto main() -> void
{
	FT_Library ft;

	auto window = std::make_unique<SE::Window>("Test", WINDOW_WIDTH, WINDOW_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SE::SimpleRenderer ren;

	Texture tex1("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\test.png");
	Texture tex("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\tree.png");

	//auto s3 = std::make_shared<SE::Rectangle>(SE::vec3(25.0f, 33.0f, 0.0f), SE::vec2(25, 25), SE::vec3(0.0, 0.0, 1.0), 1);
	//auto s2 = std::make_shared<SE::TestCollisionalRectangle1>(SE::vec3(50.0f, 100.0f, 0.0f), SE::vec2(50, 50), SE::vec3(1.0, 0.0, 1.0), 8);
	//auto s1 = std::make_shared<SE::TestCollisionalRectangle2>(SE::vec3(30.0f, 40.0f, 0.0f), SE::vec2(100, 100), SE::vec3(0.0, 1.0, 0.0), 7);

	auto s2 = std::make_shared<SE::Rectangle>(SE::vec3(70.0f, 70, 0.0f), SE::vec2(100, 100), tex1, 1);
	auto s1 = std::make_shared<SE::Rectangle>(SE::vec3(50, 50, 0.0f), SE::vec2(100, 50), tex, 2);

	SE::Application app;
	//auto s1 = std::make_shared<Sprite>(vec3(3.0f, 4.0f, 0.0f), vec2(10,10), vec3(0.0, 1.0, 0.0), 0);
	//auto s2 = std::make_shared<Sprite >(vec3(50.0f, 100.0f, 0.0f),vec2(50,50), vec3(1.0, 0.0, 1.0), 1);

	SE::InputManager::getInstance().init(window.get()->getWindow());
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveLeft, s1.get()), GLFW_KEY_A);
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveRight, s1.get()), GLFW_KEY_D);
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveUp, s1.get()), GLFW_KEY_W);
	SE::InputManager::getInstance().registerSpriteAction(std::bind(&SE::Rectangle::moveDown, s1.get()), GLFW_KEY_S);
	//or even

	float inc = -2.0f;
	//auto funcPointer = static_cast<void(Sprite::*)(const vec3&)>(&Sprite::UpdateLocation);
	//InputManager::getInstance().registerSpriteAction(std::bind(funcPointer, s3.get(), s3->m_position.add(vec3(10, 10, 0.0f))), GLFW_KEY_S);

	ren.addRectangleToDrawCall(s1);
	
	ren.addRectangleToDrawCall(s2);
	ren.removeRectangleFromDrawCall(s2);
	//ren.addToDrawCall(s3);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);
	//float inc = -0.1f;

	SE::LabelManager::getInstance().setIsDisplayingFps(true);
	SE::LabelManager::getInstance().addLabel(SE::Label("Hello World!", 250, 300));
	std::cout << 550 * 100 / WINDOW_WIDTH;


	SE::test *t1 = new SE::test();

	SE::CollisionManager::addCollisionalEntities(s1, s2, std::bind(&SE::test::method, t1, std::placeholders::_1, std::placeholders::_2));

	while (!window->closed())
	{
		window->clear();

		ren.draw();
		SE::LabelManager::getInstance().displayAllLabels();
		SE::CollisionManager::checkCollisions();

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#else

auto main()->int
{
	glEnable(GL_DEPTH_TEST);
	auto window = std::make_unique<SE::Window>("Test", WINDOW_WIDTH, WINDOW_HEIGHT);

	SE::SimpleRenderer ren;

	Texture tex("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\tree.png");
	Texture tex1("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\test.png");

	auto s1 = std::make_shared<SE::Rectangle>(SE::vec3(0, 0, 0.0f), SE::vec2(200, 200), tex1, 1);
	//auto s2 = std::make_shared<SE::Rectangle>(SE::vec3(70.0f, 70, 0.0f), SE::vec2(100, 100), tex1, 4);
	//auto s3 = std::make_shared<SE::Rectangle>(SE::vec3(150.0f, 10, 0.0f), SE::vec2(10, 10), SE::vec3(1, 0, 0), 0);
	//auto s4 = std::make_shared<SE::Rectangle>(SE::vec3(10.0f, 10, 0.0f), SE::vec2(100, 100), SE::vec3(0, 1, 0), 3);

	Texture tex2("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\kitty.png");
	auto s3 = std::make_shared<SE::Rectangle>(SE::vec3(100.0f, 100.0f, 0.0f), SE::vec2(50, 50), SE::vec3(1, 1, 1), tex, 2);

	auto l1 = std::make_shared<SE::Light>();
	l1->addLight("l1", SE::vec3(0, 0, 50));
	l1->addLight("l2", SE::vec3(200, 200, 25));
	
	ren.addRectangleToDrawCall(s1);
	//ren.addToDrawCall(s2);
	ren.addRectangleToDrawCall(s3);
	//ren.addToDrawCall(s4);
	ren.addLightToDrawCall(l1);


	while (!window->closed())
	{
		//nullTexture.bind();
		window->clear();

		ren.draw();

		window->update();
		//nullTexture.unbind();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return 0;
}
#endif