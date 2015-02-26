#pragma once
#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "EntityBase.h"
#include "SpriteBase.h"
#include "StateBase.h"

#include "StateMainMenu.h"

using std::vector;

class Application{
public:
	Application();
	~Application();

	void Init();
	bool Run();
	
	void ProcessEvents();
	void Update(float elapsed);
	void Render(float elapsed);

private:
	bool done;
	float lastFrameTicks;

	SDL_Window* displayWindow;
	std::vector<EntityBase*> entities;

	StateMainMenu mainMenu;
	//gameLevel

};

