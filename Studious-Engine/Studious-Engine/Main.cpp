#include "Window.h"
#include "Shader.h"

#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"

auto main() -> void
{
	auto window = new Window("Test", 600, 800);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Shader shader("basic.vert", "basic.frag");
	//shader.enable();

	//Sprite s1(0.5f, 1.0f, 0.5f, 1.0f, 1.0, 0.0, 0.0);
	Sprite s1(vec4(0.5f, 1.0f, 0.5f, 1.0f), vec3(1.0, 0.0, 0.0), 0);

	//Sprite s2(-0.5f, -1, -0.5, -1, 1.0, 0.0, 1.0);
	Sprite s2(vec4(-0.5f, -1.0f, -0.5f, -1.0f), vec3(1.0, 0.0, 1.0), 0);

	InputManager::getInstance().init(window->getGLFWWindow());

	InputManager::getInstance().registerSpriteAction(GLFW_KEY_W, s1);

	SimpleRenderer ren;
	ren.addToDrawCall(s1);
	ren.addToDrawCall(s2);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);

	while (!window->closed())
	{
		window->clear();
		//s1.UpdateLocation(s1.getPosition().x, s1.getPosition().y, s1.getPosition().z, s1.getPosition().w);
		//s1.Draw();
		//s2.Draw();
		ren.draw();

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete window;
}