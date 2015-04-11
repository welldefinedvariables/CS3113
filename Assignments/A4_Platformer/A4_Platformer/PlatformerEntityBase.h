#pragma once
#include <array>

#include "EntityBase.h"
#define FIXED_TIMESTEP 0.01666666f
#define MAX_TIMESTEPS 6

class PlatformerEntityBase : public EntityBase
{
public:
	PlatformerEntityBase(float x, float y);
	~PlatformerEntityBase();

	void Update(float elapsed);
	void UpdateX(float elapsed);
	void UpdateY(float elapsed);
	bool CollideX(const std::array<float, 4> &rect2);
	bool CollideY(const std::array<float, 4> &rect2);
	void ResetCollide();
	void HandleCollision(float elapsed);


	void Render(float elapsed) = 0;
	const std::array<float, 4> getRect() const = 0;

	void Left();
	void Right();
	void Up();
	void Down();
	void StopLR();

	bool isColliding(const std::array<float, 4> &rect, const std::array<float, 4> &rect2);
	

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
