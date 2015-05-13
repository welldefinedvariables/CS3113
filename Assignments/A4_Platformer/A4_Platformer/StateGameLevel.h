#pragma once

#include "StateBase.h"

#include "EntityBase.h"
#include "Entity.h"

#include "AnimatedSprite.h"

#include "Enemy.h"
#include "Bullet.h"


#include "PlatformerEntity.h"

#include <ctime>
#include <array>
#include <vector>
using std::array;
using std::vector;

class StateGameLevel:public StateBase{
public:
	StateGameLevel();
	~StateGameLevel();

	void Init();

	void ProcessEvents(SDL_Event& event);
	void Update(float elapsed);
	void Render(float elapsed);
	void detectCollisionX(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities);
	void detectCollisionY(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities);

	unsigned int getScore() const;
	void Reset();
private:
	unsigned int score;
	
	AnimatedSprite *test;
	vector<PlatformerEntity*> platformEntities;
	PlatformerEntity* player;
};