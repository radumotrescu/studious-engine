#include "Window.h"
#include "Shader.h"

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

using namespace std;

auto main() -> void
{
	auto window = new Window("Test", 600, 800);


	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	std::vector<GLfloat>vertices
	{
		0, 0,
		0, 0.5,
		1, 0.5,
		1, 0,
		0, -0.5,
		-1, -0.5,
		-1, 0
	};

	std::vector<GLushort> elements
	{
		0, 1, 2,
		//2, 3, 0
		4,5,6
	};

	std::vector<GLfloat> colors
	{
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1
	};
	//GLushort elements[] =
	//{ 
	//	2,3,0,
	//	0,1,3,

	//};
	VertexArray sprite1;
	IndexBuffer ibo(elements, elements.size());

	sprite1.addBuffer(std::make_shared<Buffer>(vertices, vertices.size(), 2), 0);
	sprite1.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);


	//GLuint vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//GLuint vbo;
	//glGenBuffers(1, &vbo); // Generate 1 buffer

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//GLuint ebo;
	//glGenBuffers(1, &ebo);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	sprite1.bind();
	ibo.bind();

	//glUniform2f(glGetUniformLocation(shader.m_shaderID, "position"), 1.0f, 0.0f);
	glUniform4f(glGetUniformLocation(shader.m_shaderID, "Color"), 1.0f, 0.0f, 0.0f, 0.0f);


	//GLint posAttrib = glGetAttribLocation(shader.m_shaderID, "position");
	//glEnableVertexAttribArray(posAttrib);
	//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

	ibo.unbind();
	sprite1.unbind();

	//GLint colAttrib = glGetAttribLocation(shader.m_shaderID, "color");
	//glEnableVertexAttribArray(colAttrib);
	//glVertexAttribPointer(colAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	while (!window->closed())
	{

		window->clear();
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		sprite1.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete window;
}