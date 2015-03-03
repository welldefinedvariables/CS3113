#pragma once

#include "StateBase.h"

#include "EntityBase.h"
#include "Entity.h"

#include "SpriteBase.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#include <ctime>
#include <array>
using std::array;

class StateGameLevel:public StateBase{
public:
	StateGameLevel();
	~StateGameLevel();

	void Init();

	void ProcessEvents(SDL_Event& event);
	void Update(float elapsed);
	void Render(float elapsed);

	unsigned int getScore() const;
	void Reset();
private:
	unsigned int score;

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	Player* player;
	Bullet* playerBullet;
	SpriteBase* bSprite;
};