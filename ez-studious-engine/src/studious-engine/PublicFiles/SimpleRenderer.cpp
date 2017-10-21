#include "SimpleRenderer.h"

namespace SE {

	SimpleRenderer::SimpleRenderer(const float screenWidth, const float screenHeight)
	{
		mat4 ortho = mat4::orthographic(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 10.0f);
		m_shader.enable();
		m_shader.setUniformMat4("pr_matrix", ortho);
		//m_shader.setUniform3fv("light", std::array<float, 6>{50, 50, 50, 0, 0, 100});
		//m_shader.setUniform1f("lintensity", 23.0f);
		m_shader.setUniform2f("lpos", Light::getPosition());
		m_shader.setUniform1i("lightEnabled", Light::getEnabled());
		//m_shader.setUniform3f("lcolor",vec3())
		m_shader.disable();
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

	auto SimpleRenderer::removeRectangleFromDrawCall(std::shared_ptr<Rectangle> sprite) -> void
	{
		m_drawVector.erase(std::remove(m_drawVector.begin(), m_drawVector.end(), sprite), m_drawVector.end());
	}

	auto SimpleRenderer::setLightStatus(const bool enabled) -> void
	{
		Light::setEnabled(enabled);
		m_shader.enable();
		m_shader.setUniform1i("lightEnabled", Light::getEnabled());
		m_shader.disable();
	}

	auto SimpleRenderer::setLightPosition(const vec2 position) -> void
	{
		Light::setPosition(position);
		m_shader.enable();
		m_shader.setUniform2f("lpos", Light::getPosition());
		m_shader.disable();
	}



	auto SimpleRenderer::draw() -> void
	{

		static auto y = 0.001;
		y += 0.001;
		if (y > 1)
			y = 0.0;
		m_shader.enable();
		for (auto& rectangle : m_drawVector)
		{
			m_shader.setUniformMat4("ml_matrix", mat4::translation(rectangle->getOrigin()));
			m_shader.setUniform1i("tex", rectangle->getTextureID());
			m_shader.setUniform2f("scrollingSpeed", vec2(rectangle->getScrollingSpeed()*y));
			//m_shader.setUniform3fv("light", m_light->getLightVector());
			rectangle->draw();


			//for (auto& light : m_lightVector)
			//{
			//	m_shader.setUniform2f("lpos", light->getPosition());
			//	m_shader.setUniform1f("lintensity", light->getIntensity());
			//}
		}
		m_shader.disable();


	}

}
