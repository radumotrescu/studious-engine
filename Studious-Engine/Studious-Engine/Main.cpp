#include "Window.h"
#include "Shader.h"

using namespace std;

auto main() -> void
{
	auto window = new Window("Test", 600, 800);


	 glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	 Shader shader("basic.vert", "basic.frag");
	 shader.enable();

	float vertices[] = {
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	while(!window->closed())
	{

		window->clear();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window->update();
	}

	delete window;
}