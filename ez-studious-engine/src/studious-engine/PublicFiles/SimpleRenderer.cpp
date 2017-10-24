#include "SimpleRenderer.h"

namespace SE 
{
	const float notMovingValue = 0.0f;
	const float fullLoopFPSValues = 1000.0f;
	const float loopIncrementValue = 1.0f;
	const float startingLoopValue = 0.0f;

	SimpleRenderer::SimpleRenderer(const float screenWidth, const float screenHeight, const float depthLevel)
	{
		const float nearPlane = -1.0f;
		const float minViewportWidth = 0.0f;
		const float minViewportHeight = 0.0f;
		mat4 ortho = mat4::orthographic(minViewportWidth, screenWidth, screenHeight, minViewportHeight, nearPlane, depthLevel);
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

	bool compareSpritePriority(const std::shared_ptr<Rectangle> s1, const std::shared_ptr<Rectangle> s2)
	{
		return s1->getPriority() < s2->getPriority();
	}

	auto SimpleRenderer::addRectangleToDrawCall(const std::shared_ptr<Rectangle> sprite) -> void
	{
		m_drawVector.push_back(sprite);
		std::sort(m_drawVector.begin(), m_drawVector.end(), compareSpritePriority);
		LoopStruct loopStruct;
		
		if (sprite->getScrollingSpeed().x != notMovingValue)
			loopStruct.m_loopInterval.x = fullLoopFPSValues / std::abs(sprite->getScrollingSpeed().x);
		else
			loopStruct.m_loopInterval.x = notMovingValue;

		if (sprite->getScrollingSpeed().y != notMovingValue)
			loopStruct.m_loopInterval.y = fullLoopFPSValues / std::abs(sprite->getScrollingSpeed().y);
		else
			loopStruct.m_loopInterval.y = notMovingValue;

		scrollingMap[sprite] = loopStruct;
	}

	auto SimpleRenderer::removeRectangleFromDrawCall(std::shared_ptr<Rectangle> sprite) -> void
	{
		m_drawVector.erase(std::remove(m_drawVector.begin(), m_drawVector.end(), sprite), m_drawVector.end());
	}

	auto SimpleRenderer::setLightStatus(const bool enabled) const -> void
	{
		Light::setEnabled(enabled);
		m_shader.enable();
		m_shader.setUniform1i("lightEnabled", enabled);
		m_shader.disable();
	}

	auto SimpleRenderer::setLightPosition(const vec2 position) const -> void
	{
		Light::setPosition(position);
		m_shader.enable();
		m_shader.setUniform2f("lpos", position);
		m_shader.disable();
	}

	auto SimpleRenderer::setLightRadius(const float radius) const -> void
	{
		Light::setRadius(radius);
		m_shader.enable();
		m_shader.setUniform1f("lradius", radius);
		m_shader.disable();
	}

	auto SimpleRenderer::setLightIntensity(const float intensity) const -> void
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
			rectangle.second.m_loopValue.x += loopIncrementValue;
			if (rectangle.second.m_loopValue.x > rectangle.second.m_loopInterval.x)
				rectangle.second.m_loopValue.x = startingLoopValue;

			rectangle.second.m_loopValue.y += loopIncrementValue;
			if (rectangle.second.m_loopValue.y > rectangle.second.m_loopInterval.y)
				rectangle.second.m_loopValue.y = startingLoopValue;
		}

		m_shader.enable();

		for (auto& rectangle : m_drawVector)
		{
			m_shader.setUniform1i("affectedByLighting", rectangle->getAffectedByLighting());
			m_shader.setUniformMat4("ml_matrix", mat4::translation(rectangle->getOrigin()));
			m_shader.setUniform1i("tex", rectangle->getTextureID());
			const vec2 scrollingOffset = vec2(rectangle->getScrollingSpeed().x*(scrollingMap[rectangle].m_loopValue.x / 1000), rectangle->getScrollingSpeed().y*(scrollingMap[rectangle].m_loopValue.y / fullLoopFPSValues));
			m_shader.setUniform2f("scrollingOffset", scrollingOffset);
			rectangle->draw();
		}
		m_shader.disable();


	}

}
