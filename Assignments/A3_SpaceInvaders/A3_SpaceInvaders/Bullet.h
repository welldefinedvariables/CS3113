#pragma once
#include "Entity.h"
#include "SpriteBase.h"

class Bullet : public Entity<SpriteBase>
{
public:

	Bullet(SpriteBase sprite, float x, float y);

	void Update(float elapsed);
	void Render(float elapsed);
	
	void Shoot(float x, float y, float direction);
	void disable();
private:
	float direction;
};
