#include "Window.h"
#include "Shader.h"

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Sprite.h"
#include "SimpleRenderer.h"

auto main() -> void
{
	auto window = new Window("Test", 600, 800);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	auto s1 = std::make_shared<Sprite>(vec3(3.0f, 4.0f, 0.0f), 10, 10, vec3(1.0, 0.0, 0.0), 2);

	auto s2 = std::make_shared<Sprite >(vec3(50.0f, 100.0f, 0.0f), 50, 50, vec3(1.0, 0.0, 1.0), 1);
	//Sprite sprite(vec3(20.0f, 30.0f, 0.0f), 40, 20, vec3(0.5, 0.2, 0.3), 1);

	SimpleRenderer ren;
	ren.addToDrawCall(s1);
	ren.addToDrawCall(s2);
	//ren.addToDrawCall(sprite);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);
	float inc = -1.0f;
	while (!window->closed())
	{
		window->clear();

		s1->UpdateLocation(s1->position.add(vec3(-inc*0.1, -inc* 0.1, 0.0)));
		if (s1->position.y  >200 || s1->position.y <0)
			inc = -inc;
		ren.draw();

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete window;
}