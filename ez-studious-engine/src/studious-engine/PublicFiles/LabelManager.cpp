#pragma once

#include <ctime>
#include <string>

#include "LabelManager.h"

namespace SE
{
	std::list<Label> LabelManager::m_labels;
	int LabelManager::m_frames;
	int LabelManager::m_initialTime;
	Label LabelManager::m_FPSLabel;
	bool LabelManager::m_displayFPS;

	auto LabelManager::getInstance() -> LabelManager&
	{
		static LabelManager labelManager;

		return labelManager;
	}

	auto LabelManager::init() -> void
	{
		m_FPSLabel = Label("FPS ", 15, 15, 1.0);
	}

	auto LabelManager::addLabel(const Label& label) -> void
	{
		m_labels.push_back(label);
	}

	auto LabelManager::displayAllLabels() -> void
	{
		if (m_displayFPS)
		{
			generateFpsCounter();
			m_FPSLabel.display();
		}

		for (auto &element : m_labels)
		{
			element.display();
		}
	}

	auto LabelManager::setIsDisplayingFps(const bool isDisplayingFps) -> void
	{
		m_displayFPS = isDisplayingFps;
		m_frames = 0;
		m_initialTime = clock();
	}

	auto LabelManager::generateFpsCounter() -> void
	{
		m_frames++;

		if ((clock() - m_initialTime) / CLOCKS_PER_SEC)
		{
			m_FPSLabel.setMessage(std::to_string(m_frames) + " FPS");
			m_initialTime = clock();
			m_frames = 0;
		}
	}
}
