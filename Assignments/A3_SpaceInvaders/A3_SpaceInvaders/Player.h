#pragma once
#include "Entity.h"
#include "SpriteBase.h"

class Player : public Entity<SpriteBase>
{
public:
	Player(SpriteBase sprite, float x, float y);

	void Update(float elapsed);
	void Render(float elapsed);
	void Left();
	void Right(); 

private:

};
