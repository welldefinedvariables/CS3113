#pragma once
#include "Entity.h"
#include "SpriteBase.h"

class Enemy : public Entity<SpriteBase>
{
public:
	Enemy(SpriteBase sprite, float x, float y, unsigned int score);

	void Update(float elapsed);
	void Render(float elapsed);

	void Move();
	void Left();
	void Right();
	void Down();

	void disable();
	unsigned int getScore();

private:
	unsigned int score;
};
