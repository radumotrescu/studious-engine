#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "SimpleRenderer.h"
#include "InputManager.h"

auto main() -> void
{
	auto window = std::make_unique<Window>("Test", 600, 800);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SimpleRenderer ren;

	auto s1 = std::make_shared<Sprite>(vec3(3.0f, 4.0f, 0.0f), vec2(10,10), vec3(0.0, 1.0, 0.0), 1);
	auto s2 = std::make_shared<Sprite>(vec3(50.0f, 100.0f, 0.0f),vec2(50,50), vec3(1.0, 0.0, 1.0), 2);
	auto s3 = std::make_shared<Sprite>(vec3(25.0f, 33.0f, 0.0f), vec2(25, 25), vec3(0.0, 0.0, 1.0), 0);

	auto s1 = std::make_shared<Sprite>(vec3(3.0f, 4.0f, 0.0f), vec2(10,10), vec3(0.0, 1.0, 0.0), 0);
	auto s2 = std::make_shared<Sprite >(vec3(50.0f, 100.0f, 0.0f),vec2(50,50), vec3(1.0, 0.0, 1.0), 1);

	ren.addToDrawCall(s1);
	ren.addToDrawCall(s2);
	ren.addToDrawCall(s3);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);
	float inc = -0.1f;
	while (!window->closed())
	{
		window->clear();
		//s1->UpdateLocation(s1->m_position.add(vec3(-inc*0.1f, -inc* 0.1f, 0.0f)));
		if (s1->m_position.y > 200 || s1->m_position.y < 0)
			inc = -inc;
		ren.draw();

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
