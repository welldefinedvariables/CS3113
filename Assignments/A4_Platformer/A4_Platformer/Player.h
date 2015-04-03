#pragma once
#include "Entity.h"
#include "SpriteBase.h"
#include "Bullet.h"

class Player : public Entity < SpriteBase >
{
public:
	Player(SpriteBase sprite, float x, float y);
	Player(SpriteBase sprite, Bullet *bullet, float x, float y);

	void Update(float elapsed);
	void Render(float elapsed);

	void Stop();

	void Left();
	void Right();

	void Shoot();

private:
	Bullet *bullet;
};
