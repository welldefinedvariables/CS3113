#pragma once
#include <array>

class EntityBase
{
public:
	EntityBase(float x, float y);
	~EntityBase();

	virtual void Update(float elapsed);
	virtual void Render(float elapsed) = 0;
	virtual const std::array<float, 4>& getRect() const = 0;

protected:
	float x;
	float y;

	float xVelocity;
	float yVelocity;

	float xAcceleration;
	float yAcceleration;

	bool enabled;
};