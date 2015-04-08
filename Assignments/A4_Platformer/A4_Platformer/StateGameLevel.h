#pragma once

#include "StateBase.h"

#include "EntityBase.h"
#include "Entity.h"

#include "SpriteBase.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


#include "PlatformerEntity.h"

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
	void detectCollisionX(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities);
	void detectCollisionY(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities);

	unsigned int getScore() const;
	void Reset();
private:
	unsigned int score;
	std::vector<PlatformerEntity*> platformEntities;
	std::vector<PlatformerEntity*> platformBlocks;
	PlatformerEntity* player;
	
	SpriteBase* bSprite;
};