#pragma once
#include "StateBase.h"

class StateMainMenu : public StateBase{
public:
	StateMainMenu();
	~StateMainMenu();

	void Init();

	void ProcessEvents();
	void Update(float elapsed);
	void Render(float elapsed);

private:
};