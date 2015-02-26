#include "StateGameLevel.h"


StateGameLevel::StateGameLevel():StateBase(){
	StateBase::Init();
	unsigned int textureID = LoadTexture("sheet.png");
	SpriteBase pSprite = SpriteBase(textureID, 211.0f/1024.0f, 941.0f/1024.0f, 99.0f/1024.0f, 75.0f/1024.0f, 1.3f, 0.0f);
	SpriteBase eSprite = SpriteBase(textureID, 423.0f / 1024.0f, 728.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 1.3f, 0.0f);
	SpriteBase bSprite = SpriteBase(textureID, 858.0f / 1024.0f, 230.0f / 1024.0f, 9.0f / 1024.0f, 54.0f / 1024.0f, 1.3f, 0.0f);

	player = new Player(pSprite, 0.0f, -0.85f);
	entities.push_back(player);
	//entities.push_back(new Player(bSprite, 1.0f, 0.0f));

}

StateGameLevel::~StateGameLevel(){}

void StateGameLevel::Init(){
	StateBase::Init();
}

void StateGameLevel::ProcessEvents(SDL_Event& event){
	if (event.type == SDL_KEYDOWN){
		if (event.key.keysym.scancode == SDL_SCANCODE_A){
			player->Left();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_D){
			player->Right();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_W){

		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
			player->Left();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
			player->Right();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){

		}
	}
}

void StateGameLevel::Update(float elapsed){
	for (int i = 0; i < entities.size(); i++){
		entities[i]->Update(elapsed);
	}
}

void StateGameLevel::Render(float elapsed){
	for (int i = 0; i < entities.size(); i++){
		entities[i]->Render(elapsed);
	}
}