#include "Score.h"
#include <string>
#include <Rectangle.h>

Score::Score()
{
	this->m_scoreLabel = SE::Label("Score: 0", 515, 15, 2);
}

auto Score::getLabel() const -> SE::Label
{
	return this->m_scoreLabel;
}

auto Score::increaseScore(std::shared_ptr<SE::Rectangle> ball, std::shared_ptr<SE::Rectangle> brick) -> void
{
	this->m_score++;
	this->m_scoreLabel.setMessage("Score: " + std::to_string(this->m_score));
}
