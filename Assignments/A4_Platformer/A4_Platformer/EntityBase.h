#pragma once
#include <array>

class EntityBase
{
public:
	EntityBase(float x, float y);
	~EntityBase();

	virtual void Update(float elapsed);
	virtual void Render(float elapsed) = 0;

	bool isEnabled() const { return enabled; }

	virtual const std::array<float, 4> getRect() const = 0;

	float lerp(float v0, float v1, float t) { return (1.0 - t)*v0 + t*v1; }
protected:
	float x;
	float y;

	float xVelocity;
	float yVelocity;

	float xAcceleration;
	float yAcceleration;

	float xFriction;
	float yFriction;

	bool enabled;
};