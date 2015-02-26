#pragma once

#include "EntityBase.h"
#include "StateBase.h"
#include "Player.h"
#include "Entity.h"
#include "SpriteBase.h"

class StateGameLevel:public StateBase{
public:
	StateGameLevel();
	~StateGameLevel();

	void Init();

	void ProcessEvents(SDL_Event& event);
	void Update(float elapsed);
	void Render(float elapsed);

private:
	std::vector<EntityBase*> entities;
	std::vector<EntityBase*> bullets;
	Player* player;
};