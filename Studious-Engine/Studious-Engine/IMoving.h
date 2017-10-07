#pragma once

class IMoving
{
protected:
	~IMoving() = default;
public:
	virtual auto action() -> void = 0;
};

