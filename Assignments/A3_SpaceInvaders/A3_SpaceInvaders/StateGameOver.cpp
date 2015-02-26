#include "StateGameOver.h"



StateGameOver::StateGameOver() :StateBase(){
	fontTexture = LoadTexture("font2.png");
}
StateGameOver::~StateGameOver(){

}



void StateGameOver::Init(){
	StateBase::Init();
}

void StateGameOver::ProcessEvents(SDL_Event& event){
	if (event.type == SDL_KEYDOWN){
		if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
			done = true;
			nextState = STATE_GAME_LEVEL;
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_Q){
			done = true;
			nextState = STATE_MAIN_MENU;
		}
	}
}
void StateGameOver::Update(float elapsed){}
void StateGameOver::Render(float elapsed){
	DrawText1(fontTexture, "sPaCe InVaDeRs", 0.15f, -0.05f, -0.6f, 0.6f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawText1(fontTexture, "PlAy AgAiN", 0.10f, -0.05f, -0.1f, 0.2f, 1.0f, 1.0f, 1.0f, 0.5f);
	DrawText1(fontTexture, " press enter", 0.10f, -0.05f, -0.3f, 0.05f, 1.0f, 1.0f, 1.0f, 0.5f);

	DrawText1(fontTexture, "Press q to go to main menu ", 0.05f, 0.0f, -0.8f, -0.4f, 0.5f, 0.5f, 0.5f, 1.0f);
	
}