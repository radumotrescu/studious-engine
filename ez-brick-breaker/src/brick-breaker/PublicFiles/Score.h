#pragma once
#include <Label.h>
#include <Rectangle.h>

class Score
{
public:
	Score();
	auto getLabel() const->SE::Label;
	auto increaseScore(std::shared_ptr<SE::Rectangle>& ball, std::shared_ptr<SE::Rectangle>& brick) -> void;
private:
	SE::Label m_scoreLabel;
	int m_score = 0;
};
