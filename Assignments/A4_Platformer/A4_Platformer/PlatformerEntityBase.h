#pragma once
#include <array>

#include "EntityBase.h"

class PlatformerEntityBase : public EntityBase
{
public:
	PlatformerEntityBase(float x, float y);
	~PlatformerEntityBase();

	void Update(float elapsed);
	void Render(float elapsed) = 0;
	const std::array<float, 4> getRect() const = 0;

	void Left();
	void Right();
	void Up();
	void Down();

	void isColliding(float x, float y, float width, float height);

	void disable();
	void setStatic();

protected:
	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;

	float mass;
	bool isStatic;
	bool enableCollisions;
};
