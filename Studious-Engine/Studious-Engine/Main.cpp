#include "Window.h"
#include "Shader.h"

using namespace std;

auto main() -> void
{
	auto window = new Window("Test", 600, 800);


	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	GLfloat vertices[] = {
		   -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		   -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	GLuint elements[] =
	{ 
		2,3,0,
		0,1,3,
		0,1,2
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shader.m_shaderID, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shader.m_shaderID, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	while (!window->closed())
	{

		window->clear();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		window->update();
	}

	delete window;
}