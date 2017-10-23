#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"
#include "CollisionChecker.h"
#include "Rectangle.h"
#include "glut.h"
#include "LabelManager.h"
#include "CollisionManager.h"
#include "Vec3.h"
#include "Light.h"
#include"SoundManager.h"

#include "gltext.h"


static const int WINDOW_WIDTH = 600;
static const int WINDOW_HEIGHT = 800;

#if 0

namespace SE {
	class test {
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

	SE::SimpleRenderer ren(WINDOW_WIDTH,WINDOW_HEIGHT,10);

	Texture tex("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\cer.png");
	Texture tex1("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\test.png");

	auto s1 = std::make_shared<SE::Rectangle>(SE::vec2(0, 0 ), SE::vec2(WINDOW_WIDTH, WINDOW_HEIGHT), tex, 1);
	s1->setScrollingSpeed(SE::vec2(1, 0));
	//auto s2 = std::make_shared<SE::Rectangle>(SE::vec3(70.0f, 70, 0.0f), SE::vec2(100, 100), tex1, 4);
	//auto s3 = std::make_shared<SE::Rectangle>(SE::vec3(150.0f, 10, 0.0f), SE::vec2(10, 10), SE::vec3(1, 0, 0), 0);
	//auto s4 = std::make_shared<SE::Rectangle>(SE::vec3(10.0f, 10, 0.0f), SE::vec2(100, 100), SE::vec3(0, 1, 0), 3);

	Texture tex2("..\\..\\src\\studious-engine\\PublicFiles\\Textures\\tree.png");
	auto s3 = std::make_shared<SE::Rectangle>(SE::vec2(100.0f, 100.0f), SE::vec2(50, 50), SE::vec3(1, 1, 1), tex2, 3);
	//s3->setScrollingSpeed(SE::vec2(1, -4));

	ren.addRectangleToDrawCall(s1);
	ren.addRectangleToDrawCall(s3);

	SE::LabelManager::init();
	SE::LabelManager::setIsDisplayingFps(true);
	ren.setLightStatus(true);
	ren.setLightPosition(SE::vec2(100, 100));
	ren.setLightRadius(200.f);
	ren.setLightIntensity(1.0f);
	auto label = SE::Label("Salut", 1, 66, 2.0);
	label.setColor(SE::vec3(0.2, 0.6, 0.01));
	SE::LabelManager::addLabel(label);


	SoundManager::init();

	auto sound = std::make_shared<Sound>("acdc", "..\\..\\src\\studious-engine\\PublicFiles\\Sounds\\acdc.mp3");
	auto sound2 = std::make_shared<Sound>("hit", "..\\..\\src\\studious-engine\\PublicFiles\\Sounds\\hit2.wav");

	SoundManager::add(sound);
	SoundManager::add(sound2);

	SoundManager::get("acdc")->loop();



	//number of frames
	int i = 0;
	while (!window->closed())
	{
		//nullTexture.bind();
		window->clear();


		ren.draw();

		SE::LabelManager::displayAllLabels();

		i++;
		if (i == 200)
		{
			SoundManager::get("hit")->loop();
		}
		if (i == 350)
		{
			SoundManager::get("acdc")->pause();
		}
		if (i == 500)
		{
			SoundManager::get("acdc")->play();
		}
		if (i == 650)
		{
			SoundManager::get("hit")->stop();
		}
		std::cout << i << std::endl;



		window->update();
		//nullTexture.unbind();
	}

	//gltDeleteText(text);
	gltTerminate();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return 0;
}
#endif