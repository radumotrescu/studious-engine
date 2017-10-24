#pragma once
#include <list>
#include "Label.h"

namespace SE
{
	class LabelManager
	{
	public:
		static auto getInstance() -> LabelManager&;
		static auto init() -> void;
		static auto addLabel(const Label&) -> void;
		static auto displayAllLabels() -> void;
		static auto setIsDisplayingFps(bool) -> void;
	private:

		static bool m_displayFPS;
		static std::list<Label> m_labels;
		static int m_frames;
		static int m_initialTime;
		static Label m_FPSLabel;

		static auto generateFpsCounter() -> void;
	};
}
