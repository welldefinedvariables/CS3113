#include "StateMainMenu.h"

StateMainMenu::StateMainMenu() :StateBase(){
	fontTexture = LoadTexture("font2.png");
}
StateMainMenu::~StateMainMenu(){
	
}



void StateMainMenu::Init(){
	StateBase::Init();
}

void StateMainMenu::ProcessEvents(SDL_Event& event){
	if (event.type == SDL_KEYDOWN){
		if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
			done = true;
			nextState = STATE_GAME_LEVEL;
		}
	}
}
void StateMainMenu::Update(float elapsed){}
void StateMainMenu::Render(float elapsed){
	DrawText1(fontTexture, "sPaCe InVaDeRs", 0.15f, -0.05f, -0.6f, 0.6f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawText1(fontTexture, "PlAy", 0.10f, -0.05f, -0.1f, 0.2f, 1.0f, 1.0f, 1.0f, 0.5f);
	DrawText1(fontTexture, " press enter", 0.10f, -0.05f, -0.3f, 0.05f, 1.0f, 1.0f, 1.0f, 0.5f);

	DrawText1(fontTexture, "Instructions: ", 0.05f, 0.0f, -0.8f, -0.4f, 0.5f, 0.5f, 0.5f, 1.0f);
	DrawText1(fontTexture, "              Left    < or a ", 0.05f, 0.0f, -0.8f, -0.5f, 0.5f, 0.5f, 0.5f, 1.0f);
	DrawText1(fontTexture, "              Right   > or d ", 0.05f, 0.0f, -0.8f, -0.6f, 0.5f, 0.5f, 0.5f, 1.0f);
	DrawText1(fontTexture, "              Shoot   space or w ", 0.05f, 0.0f, -0.8f, -0.7f, 0.5f, 0.5f, 0.5f, 1.0f);

}