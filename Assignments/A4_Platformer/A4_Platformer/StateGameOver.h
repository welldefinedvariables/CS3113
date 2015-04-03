#pragma once
#include "StateBase.h"


class StateGameOver : public StateBase{
public:
	StateGameOver();
	~StateGameOver();

	void Init();

	void ProcessEvents(SDL_Event& event);
	void Update(float elapsed);
	void Render(float elapsed);

private:
	
};