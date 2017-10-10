#include "SimpleRenderer.h"


SimpleRenderer::SimpleRenderer()
{
	mat4 ortho = mat4::orthographic(0.0f, 200.0f, 200.0f, 0.0f, -1.0f, 1.0f);
	m_shader.enable();
	m_shader.setUniformMat4("pr_matrix", ortho);
	//m_shader.setUniformMat4("ml_matrix", mat4::translation(vec3(50, 50, 0)));
}


SimpleRenderer::~SimpleRenderer()
{
	m_shader.disable();
}

bool compareSpritePriority(std::shared_ptr<stud::Rectangle>s1, std::shared_ptr<stud::Rectangle>s2)
{
	return s1->getPriority() > s2->getPriority();
}

auto SimpleRenderer::addToDrawCall(std::shared_ptr<stud::Rectangle> sprite) -> void
{
	m_drawVector.push_back(sprite);
	std::sort(m_drawVector.begin(), m_drawVector.end(), compareSpritePriority);
}

auto SimpleRenderer::draw() -> void
{
	for (auto& sprite : m_drawVector)
	{
		m_shader.setUniformMat4("ml_matrix", mat4::translation(sprite->getOrigin()));
		//sprite->getSprite().getShader().setUniformMat4("ml_matrix", mat4::translation(vec3(10,10,0)));
		//sprite->getSprite().getShader().setUniformMat4("ml_matrix", mat4::translation(sprite->getOrigin()));
		sprite->getSprite().Draw();
	}
}
