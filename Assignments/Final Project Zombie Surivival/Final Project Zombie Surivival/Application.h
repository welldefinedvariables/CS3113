#pragma once
#include <SDL.h>
#include <SDL_opengl.h>

class Application{
public:
	Application();
	~Application();

	
	bool Run();
	

private:
	bool done;
};

