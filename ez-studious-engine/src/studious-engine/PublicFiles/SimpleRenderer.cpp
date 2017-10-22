#include "SimpleRenderer.h"

namespace SE {

	SimpleRenderer::SimpleRenderer(const float screenWidth, const float screenHeight)
	{
		mat4 ortho = mat4::orthographic(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 10.0f);
		m_shader.enable();
		m_shader.setUniformMat4("pr_matrix", ortho);
		m_shader.setUniform2f("lpos", Light::getPosition());
		m_shader.setUniform1i("lightEnabled", Light::getEnabled());
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
		LoopStruct loopStruct;
		if (sprite->getScrollingSpeed().x != 0)
			loopStruct.m_loopInterval.x = 1000 / std::abs(sprite->getScrollingSpeed().x);
		else
			loopStruct.m_loopInterval.x = 0;
		if (sprite->getScrollingSpeed().y != 0)
			loopStruct.m_loopInterval.y = 1000 / std::abs(sprite->getScrollingSpeed().y);
		else
			loopStruct.m_loopInterval.y = 0;

		scrollingMap[sprite] = loopStruct;

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

	auto SimpleRenderer::setLightRadius(const float radius) -> void
	{
		Light::setRadius(radius);
		m_shader.enable();
		m_shader.setUniform1f("lradius", radius);
		m_shader.disable();
	}

	auto SimpleRenderer::setLightIntensity(const float intensity) -> void
	{
		Light::setIntensity(intensity);
		m_shader.enable();
		m_shader.setUniform1f("lintensity", intensity);
		m_shader.disable();
	}



	auto SimpleRenderer::draw() -> void
	{

		for (auto& rectangle : scrollingMap)
		{
			rectangle.second.m_loopValue.x += 1;
			if (rectangle.second.m_loopValue.x > rectangle.second.m_loopInterval.x)
				rectangle.second.m_loopValue.x = 0;

			rectangle.second.m_loopValue.y += 1;
			if (rectangle.second.m_loopValue.y > rectangle.second.m_loopInterval.y)
				rectangle.second.m_loopValue.y = 0;
		}

		m_shader.enable();
		for (auto& rectangle : m_drawVector)
		{
			m_shader.setUniformMat4("ml_matrix", mat4::translation(rectangle->getOrigin()));
			m_shader.setUniform1i("tex", rectangle->getTextureID());
			vec2 scrollingSpeedVec2 = vec2(rectangle->getScrollingSpeed().x*(scrollingMap[rectangle].m_loopValue.x / 1000), rectangle->getScrollingSpeed().y*(scrollingMap[rectangle].m_loopValue.y / 1000));
			m_shader.setUniform2f("scrollingSpeed", scrollingSpeedVec2);
			rectangle->draw();

		}
		m_shader.disable();


	}

}
