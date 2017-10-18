#include "SimpleRenderer.h"

namespace SE {

	SimpleRenderer::SimpleRenderer()
	{
		mat4 ortho = mat4::orthographic(0.0f, 200.0f, 200.0f, 0.0f, -1.0f, 10.0f);
		m_shader.enable();
		m_shader.setUniformMat4("pr_matrix", ortho);
		//m_shader.setUniform3fv("light", std::array<float, 6>{50, 50, 50, 0, 0, 100});
		//m_shader.setUniform1f("lintensity", 23.0f);
		m_shader.setUniform2f("lpos", vec2(100, 75));
		//m_shader.setUniform3f("lcolor",vec3())
	}


	SimpleRenderer::~SimpleRenderer()
	{
		m_shader.disable();
	}

	bool compareSpritePriority(std::shared_ptr<Rectangle>s1, std::shared_ptr<Rectangle>s2)
	{
		return s1->getPriority() < s2->getPriority();
	}

	auto SimpleRenderer::addRectangleToDrawCall(std::shared_ptr<Rectangle> sprite) -> void
	{
		m_drawVector.push_back(sprite);
		std::sort(m_drawVector.begin(), m_drawVector.end(), compareSpritePriority);
	}

	auto SimpleRenderer::addLightToDrawCall(std::shared_ptr<Light> light) -> void
	{
		m_light = light;
	}



	auto SimpleRenderer::draw() -> void
	{
		for (auto& rectangle : m_drawVector)
		{
			m_shader.setUniformMat4("ml_matrix", mat4::translation(rectangle->getOrigin()));
			m_shader.setUniform1i("tex", rectangle->getTextureID());
			//m_shader.setUniform3fv("light", m_light->getLightVector());
			rectangle->getSprite().Draw();

			for (int i = 0; i < 2;i++)
				m_shader.setUniform2f("lpos", vec2(100+50*i, 75+50*i));

			//for (auto& light : m_lightVector)
			//{
			//	m_shader.setUniform2f("lpos", light->getPosition());
			//	m_shader.setUniform1f("lintensity", light->getIntensity());
			//}
		}


	}

}
