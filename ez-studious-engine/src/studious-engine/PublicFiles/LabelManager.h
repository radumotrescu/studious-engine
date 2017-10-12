#pragma once
#include <list>
#include "Label.h"

namespace SE
{
	class LabelManager
	{
	public:
		static auto getInstance() -> LabelManager&;
		static auto addLabel(const Label&) -> void;
		auto displayAllLabels() const -> void;
		auto setIsDisplayingFps(bool) -> void;
	private:

		bool m_displayFPS = false;
		static std::list<Label> m_labels;
		static int m_frames;
		static int m_initialTime;
		static Label m_FPSLabel;

		static auto generateFpsCounter() -> void;
	};
}
