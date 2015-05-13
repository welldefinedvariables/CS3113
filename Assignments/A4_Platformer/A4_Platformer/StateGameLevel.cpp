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
	test = nullptr;
	score = 0;
	fontTexture = LoadTexture("font2.png");

	unsigned int charss = LoadTexture("sprites.png");
	unsigned int blockss = LoadTexture("sprites2.png");
	unsigned int yetiss = LoadTexture("yetiss.png");

	AnimatedSprite *coin = new AnimatedSprite(blockss, 384.0, 384.0);
	coin->addFramePixels(5.0, 5.0, 47.0, 47.0);
	coin->addSequence({ 0 });
	coin->scale(0.33);

	AnimatedSprite *snowblock = new AnimatedSprite(blockss, 384.0, 384.0);
	snowblock->addFramePixels(5.0, 155.0, 70.0, 70.0);
	snowblock->scaleXY(1.0, 12.0);
	snowblock->addSequence({ 0 });
	
	AnimatedSprite *snowground = new AnimatedSprite(blockss, 384.0, 384.0);
	snowground->addFramePixels(165.0, 155.0, 70.0, 70.0);
	snowground->scaleXY(16, 1.0);
	snowground->addSequence({ 0 });

	AnimatedSprite *snowblock2 = new AnimatedSprite(blockss, 384.0, 384.0);
	snowblock2->addFramePixels(165.0, 155.0, 70.0, 70.0);
	snowblock2->scaleXY(1.0, 1.0);
	snowblock2->addSequence({ 0 });

	AnimatedSprite *door = new AnimatedSprite(blockss, 384.0, 384.0);
	door->addFramePixels(62.0, 5.0, 70.0, 140.0);
	door->addFramePixels(142.0, 5.0, 70.0, 140.0);
	door->addSequence({ 0 });
	door->addSequence({ 0,1 });
	door->setFramesPerSecond(1.0);
	door->scale(1.0);

	AnimatedSprite *mine = new AnimatedSprite(blockss, 384.0, 384.0);

	mine->addFramePixels(222.0, 5.0, 62.0, 62.0);
	mine->addFramePixels(222.0, 77.0, 62.0, 62.0);
	mine->addFramePixels(245.0, 149.0, 62.0, 62.0);
	mine->addFramePixels(245.0, 221.0, 62.0, 62.0);
	mine->addSequence({ 0, 1 });
	mine->addSequence({ 2, 3 });
	mine->setFramesPerSecond(5.0);
	mine->scale(0.6);


	AnimatedSprite *kid = new AnimatedSprite(charss, 256.0, 256.0);
	kid->addFramePixels(64.0, 0.0, 16.0, 16.0);
	kid->addFramePixels(48.0, 16.0, 16.0, 16.0);
	kid->addFramePixels(64.0, 16.0, 16.0, 16.0);
	kid->addFramePixels(80.0, 16.0, 16.0, 16.0);
	kid->addFramePixels(48.0, 32.0, 16.0, 16.0);
	kid->addFramePixels(64.0, 32.0, 16.0, 16.0);
	kid->addFramePixels(80.0, 32.0, 16.0, 16.0);

	kid->addSequence({ 0 });
	kid->addSequence({ 1, 2, 3 });
	kid->addSequence({ 4, 5, 6 });

	kid->scale(2.5);
	kid->setFramesPerSecond(8.0);

	kid->animate(0);
	kid->enableLooping();

	AnimatedSprite *yeti = new AnimatedSprite(yetiss, 1024.0f, 1024.0f);
	yeti->scale(3.0);
	//stand
	yeti->addFramePixels(822.0, 126.0, 100.0, 107.0);
	yeti->addFramePixels(838.0, 243.0, 100.0, 107.0);
	yeti->addFramePixels(838.0, 360.0, 100.0, 107.0);

	//move
	yeti->addFramePixels(707.0, 259.0, 121.0, 111.0);
	yeti->addFramePixels(707.0, 380.0, 121.0, 111.0);
	yeti->addFramePixels(605.0, 726.0, 121.0, 111.0);
	yeti->addFramePixels(822.0, 5.0, 121.0, 111.0);

	//attack
	yeti->addFramePixels(5.0, 5.0, 224.0, 191.0);
	yeti->addFramePixels(239.0, 5.0, 224.0, 191.0);
	yeti->addFramePixels(473.0, 5.0, 224.0, 191.0);
	yeti->addFramePixels(5.0, 206.0, 224.0, 191.0);
	yeti->addFramePixels(239.0, 206.0, 224.0, 191.0);
	yeti->addFramePixels(473.0, 206.0, 224.0, 191.0);
	yeti->addFramePixels(5.0, 407.0, 224.0, 191.0);
	yeti->addFramePixels(239.0, 407.0, 224.0, 191.0);
	yeti->addFramePixels(473.0, 407.0, 224.0, 191.0);

	//die

	yeti->addFramePixels(5.0, 608.0, 190.0, 108.0);
	yeti->addFramePixels(205.0, 608.0, 190.0, 108.0);
	yeti->addFramePixels(405.0, 608.0, 190.0, 108.0);
	yeti->addFramePixels(605.0, 608.0, 190.0, 108.0);
	yeti->addFramePixels(5.0, 726.0, 190.0, 108.0);

	yeti->addSequence({ 0, 1, 2 });
	yeti->addSequence({ 3, 4, 5, 6 });
	yeti->addSequence({ 7, 8, 9, 10, 11, 12, 13, 14, 15 });
	yeti->addSequence({ 16, 17, 18, 19, 20 });
	yeti->setFramesPerSecond(10.0);
	yeti->setAlignQuadBottomRight();

	

	platformEntities.push_back(new PlatformerEntity(*snowground, 0.0, -1.0 + snowground->getHeight() / 2));
	platformEntities.push_back(new PlatformerEntity(*snowground, 0.6, -1.0 + 7*snowground->getHeight() / 2));
	platformEntities.push_back(new PlatformerEntity(*snowground, -0.6, -1.0 + 13 * snowground->getHeight() / 2));
	platformEntities.push_back(new PlatformerEntity(*snowblock, -1.33 + snowblock->getWidth() / 2, 0.0));
	platformEntities.push_back(new PlatformerEntity(*snowblock, 1.33 - snowblock->getWidth() / 2, 0.0));
	platformEntities.push_back(new PlatformerEntity(*door, -0.9, -1.0 + 14 * snowground->getHeight() / 2 + door->getHeight()/2 ));
	platformEntities.push_back(new PlatformerEntity(*snowblock2,- 0.9 +door->getWidth() + snowblock2->getWidth(), -1.0 + 14 * snowground->getHeight() / 2 + snowblock2->getHeight() / 2));
	
	
	platformEntities.push_back(new PlatformerEntity(*yeti, 0, -1.0 + 14 * snowground->getHeight() / 2 ));
	player = new PlatformerEntity(*kid, 0.0, -1.0 + snowground->getHeight() + kid->getHeight()/2  );

	//test = mine;
	//test->setFramesPerSecond(1.0);
	//test->animate(1);
	//test->enableLooping();
	//test->scale(0.5);
	//test->scaleXY(0.5, 10.5);
	// 48.0, 0.0, 16.0, 16.0
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
		if (event.key.keysym.scancode == SDL_SCANCODE_A){
			player->Left();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_D){
			player->Right();
		}
	}
	else if(event.type == SDL_KEYUP){
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d){
			player->StopLR();
		}
	}
}

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
	/*
	for (int i = 0; i < platformBlocks.size(); i++){
		platformBlocks[i]->ResetCollide();
		platformBlocks[i]->UpdateY(elapsed);

		platformBlocks[i]->UpdateX(elapsed);
	}
	
	for (int i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->ResetCollide();
		platformEntities[i]->UpdateY(elapsed);
		detectCollisionY(platformEntities[i], platformBlocks);
		platformEntities[i]->UpdateX(elapsed);
		detectCollisionX(platformEntities[i], platformBlocks);
		platformEntities[i]->HandleCollision(elapsed);
	}
	*/

	player->ResetCollide();
	player->UpdateY(elapsed);
	//detectCollisionY(player, platformBlocks);
	detectCollisionY(player, platformEntities);

	player->UpdateX(elapsed);
	//detectCollisionX(player, platformBlocks);
	detectCollisionX(player, platformEntities);

	player->HandleCollision(elapsed);
	
}

void StateGameLevel::Render(float elapsed){
	//DrawText1(fontTexture, "Score: " +std::to_string(score), 0.075f, 0.0f, 0.5f, 0.9f, 1.0f, 0.0f, 0.0f, 0.5f);
	if (test != nullptr){
		test->Draw(elapsed, 0.0f, 0.0f);
	}
	/*
	for (int i = 0; i < platformBlocks.size(); i++){
		platformBlocks[i]->Render(elapsed);
	}
	*/
	for (int i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->Render(elapsed);
	}
	player->Render(elapsed);
	

}

unsigned int StateGameLevel::getScore() const{
	return score;
}

void StateGameLevel::Reset(){

	
}