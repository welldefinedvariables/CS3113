#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

enum GAMESTATE { STATE_CURRENT, STATE_MAIN_MENU, STATE_GAME_LEVEL , STATE_GAME_OVER};

class StateBase{
public:
	StateBase();
	virtual void Init() = 0;

	virtual void ProcessEvents(SDL_Event& event) = 0;
	virtual void Update(float elapsed) = 0;
	virtual void Render(float elapsed) = 0;

	bool isDone() const;
	GAMESTATE getNextState() const;
	
protected:
	bool done;
	GAMESTATE nextState;
	GLuint fontTexture;
};

GLuint LoadTexture(const char *image_path);
void DrawText1(int fontTexture, string text, float size, float spacing, float x, float y, float r, float g, float b, float a);