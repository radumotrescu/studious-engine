#include "Window.h"
#include "Shader.h"

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct Sprite {
	std::vector<GLfloat> position;
	std::vector<GLfloat> colors;
	VertexArray vao;
	IndexBuffer ibo;
	std::vector<GLushort> indexes = {
		0,2,3,
		1,2,0
	};
	GLfloat m_pos1;
	GLfloat m_pos2;
	GLfloat m_pos3;
	GLfloat m_pos4;
	Sprite(GLfloat pos1, GLfloat pos2, GLfloat pos3, GLfloat pos4, GLfloat R, GLfloat G, GLfloat B)
	{
		m_pos1 = pos1;
		m_pos2 = pos2;
		m_pos3 = pos3;
		m_pos4 = pos4;
		ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
		position = { 0,0,0,m_pos1,m_pos2,m_pos3,m_pos4,0 };
		colors = { R,G,B,1.0f,R,G,B,1.0f,R,G,B,1.0f,R,G,B,1.0f };
		//ibo = IndexBuffer(indexes, static_cast<GLsizei>(indexes.size()));
		vao.addBuffer(std::make_shared<Buffer>(position, position.size(), 2), 0);
		vao.addBuffer(std::make_shared<Buffer>(colors, colors.size(), 4), 1);

	}

	auto UpdateLocation(const GLfloat pos1, const GLfloat pos2, const  GLfloat pos3, const  GLfloat pos4)->void
	{
		
		m_pos1 = pos1;
		m_pos2 = pos2;
		m_pos3 = pos3;
		m_pos4 = pos4;
		position[3] = m_pos1;
		position[4] = m_pos2;
		position[5] = m_pos3;
		position[6] = m_pos4;
		vao.addBuffer(std::make_shared<Buffer>(position, position.size(), 2), 0);
	}
	auto Draw()->void
	{

		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao.unbind();
	}
};

auto main() -> void
{
	auto window = new Window("Test", 600, 800);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Shader shader("basic.vert", "basic.frag");
	shader.enable();

	Sprite s1(0.5f, 1.0f, 0.5f, 1.0f, 1.0, 0.0, 0.0);
	Sprite s2(-0.5f, -1, -0.5, -1, 1.0, 0.0, 1.0);
	//auto y = glGetUniformLocation(shader.m_shaderID, "lpos");
	//glUniform2f(y, 0.0f, 0.0f);

	float inc = 0.001f;

	while (!window->closed())
	{

		window->clear();
		if (s1.position[3] <= 0.0f || s1.position[3] >= 1.0f)
			inc = -inc;
		s1.UpdateLocation(s1.m_pos1 - inc, s1.m_pos2, s1.m_pos3, s1.m_pos4);
		////if (colors[44] <= -0.5f || vertices[0] >= 0.5f)
		//if (colors[44] <= 0.0f || colors[44] >= 1.0f)
		//	inc = -inc;


		s1.Draw();
		s2.Draw();

		window->update();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete window;
}