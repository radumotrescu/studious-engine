#pragma once
#include "IEntity.h"
#include <glew.h>

class Square : public IEntity
{
private:
	float m_xCoordinate, m_yCoordinate;
	float m_size;

public:
	Square();

	auto display() -> void override;

	~Square();
};

