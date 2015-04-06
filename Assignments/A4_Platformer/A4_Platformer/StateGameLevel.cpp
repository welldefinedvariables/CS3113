#include "StateGameLevel.h"
float bulletsPerSecond = 3.0f;
float timeElapsed = 0.0f;

bool hasCollided(const array<float, 4>& rect1, const array<float, 4>& rect2){
	return (abs(rect1[0] - rect2[0]) <= (rect1[2] + rect2[2]) / 2 &&
		abs(rect1[1] - rect2[1]) <= (rect1[3] + rect2[3]) / 2);
}

//Not useful
bool hasCollided(const array<float, 4> &rect1, vector<const array<float, 4>> &rects){
	for (int i = 0; i < rects.size(); i++){
		if (hasCollided(rect1, rects[i])){
			return true;
		}
	}
	return false;
}

template<typename T>
vector<const array<float, 4>> getRects(vector< T*> entities){
	vector<const array<float, 4>> entityRects;
	for (int i = 0; i < entities.size(); i++){
		entityRects.push_back(entities[i]->getRect());
	}
	return entityRects;
}


StateGameLevel::StateGameLevel():StateBase(), score(0){

}

StateGameLevel::~StateGameLevel(){}

void StateGameLevel::Init(){
	StateBase::Init();
	unsigned int textureID = LoadTexture("sheet.png");

	fontTexture = LoadTexture("font2.png");

	unsigned int textureID2 = LoadTexture("sprites.png");
	unsigned int blocktype1 = LoadTexture("slice03_03.png");
	unsigned int blocktype2 = LoadTexture("slice33_33.png");

	SpriteBase blockSprite = SpriteBase(blocktype1, 0.0f / 1024.0f, 0.0f / 1024.0f, 70.0f / 1024.0f, 70.0f / 1024.0f, 2.0f, 0.0f);
	SpriteBase blockSprite2 = SpriteBase(blocktype2, 0.0f / 1024.0f, 0.0f / 1024.0f, 70.0f / 1024.0f, 70.0f / 1024.0f, 2.0f, 0.0f);
	SpriteBase playerSprite = SpriteBase(textureID2, 0.0f / 1024.0f, 0.0f / 1024.0f, 70.0f / 1024.0f, 70.0f / 1024.0f, 2.0f, 0.0f);
	for (int i = -10; i < 11; i++){
		platformEntities.push_back(new PlatformerEntity(blockSprite, i*blockSprite.getWidth(), -1.0f + blockSprite.getHeight() / 2));
	}
	for (size_t i = 0; i < 14; i++){
		platformEntities.push_back(new PlatformerEntity(blockSprite2, -1.333f + blockSprite2.getWidth() / 2, -1.0f + 1.5* blockSprite2.getHeight() + blockSprite2.getHeight()*i));
	}
	for (size_t i = 0; i < 14; i++){
		platformEntities.push_back(new PlatformerEntity(blockSprite2, 1.333f - blockSprite2.getWidth() / 2, -1.0f + 1.5* blockSprite2.getHeight() + blockSprite2.getHeight()*i));
	}
	for (size_t i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->setStatic();
	}
	player = new PlatformerEntity(playerSprite, 0.0f, 0.0f);

	Reset();
}

void StateGameLevel::ProcessEvents(SDL_Event& event){
	//const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	if (event.type == SDL_KEYDOWN){
		if (!event.key.repeat){
			if (event.key.keysym.scancode == SDL_SCANCODE_W){
				player->Up();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
				done = true;
				nextState = STATE_MAIN_MENU;
			}
		}
		if (event.key.keysym.sym == SDLK_a){
			player->Left();
		}
		else if (event.key.keysym.sym == SDLK_d){
			player->Right();
		}
	}
	else if(event.type == SDL_KEYUP){
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d){
			player->StopLR();
		}
	}
}

/*void StateGameLevel::handleCollision(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities){
	for (size_t i = 0; i < entities.size(); i++){
		entity->isColliding(entities[i]->getRect());
	}

}*/


void StateGameLevel::detectCollisionX(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities){
	for (size_t i = 0; i < entities.size(); i++){
		entity->CollideX(entities[i]->getRect());
	}

}

void StateGameLevel::detectCollisionY(PlatformerEntity* entity, std::vector<PlatformerEntity*> &entities){
	for (size_t i = 0; i < entities.size(); i++){
		entity->CollideY(entities[i]->getRect());
	}

}

void StateGameLevel::Update(float elapsed){
	for (int i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->ResetCollide();
		platformEntities[i]->UpdateY(elapsed);

		platformEntities[i]->UpdateX(elapsed);
	}
	player->ResetCollide();
	player->UpdateY(elapsed);
	detectCollisionY(player, platformEntities);
	player->UpdateX(elapsed);
	detectCollisionX(player, platformEntities);
	player->HandleCollision(elapsed);
	
}

void StateGameLevel::Render(float elapsed){
	//DrawText1(fontTexture, "Score: " +std::to_string(score), 0.075f, 0.0f, 0.5f, 0.9f, 1.0f, 0.0f, 0.0f, 0.5f);
	for (int i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->Render(elapsed);
	}
	player->Render(elapsed);
}

unsigned int StateGameLevel::getScore() const{
	return score;
}

void StateGameLevel::Reset(){
	score = 0;
	
}