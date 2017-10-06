#include "SimpleRenderer.h"


SimpleRenderer::SimpleRenderer()
{
	mat4 ortho = mat4::orthographic(0.0f, 200.0f, 200.0f, 0.0f, -1.0f, 1.0f);
	m_shader.enable();
	m_shader.setUniformMat4("pr_matrix", ortho);
	//m_shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
}


SimpleRenderer::~SimpleRenderer()
{
	m_shader.disable();
}

bool compareSpritePriority(std::shared_ptr<Sprite >s1, std::shared_ptr<Sprite >s2)
{
	return s1->getPriority() > s2->getPriority();
}

auto SimpleRenderer::addToDrawCall(std::shared_ptr<Sprite> sprite) -> void
{
	sprite->m_shader = m_shader;
	m_drawVector.push_back(sprite);
	std::sort(m_drawVector.begin(), m_drawVector.end(),compareSpritePriority);
}

auto SimpleRenderer::draw() -> void
{
	for (auto& sprite : m_drawVector)
	{

	sprite->m_shader.setUniformMat4("ml_matrix", mat4::translation(sprite->position));
		sprite->Draw();
	}
}
