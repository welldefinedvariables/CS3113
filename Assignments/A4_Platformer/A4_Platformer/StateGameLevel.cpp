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
	unsigned int textureID = LoadTexture("sheet.png");
	
	fontTexture = LoadTexture("font2.png");

	unsigned int textureID2 = LoadTexture("sprites.png");
	unsigned int blocktype1 = LoadTexture("slice03_03.png");
	unsigned int blocktype2 = LoadTexture("slice33_33.png");

	SpriteBase blockSprite = SpriteBase(blocktype1, 0.0f / 1024.0f, 0.0f / 1024.0f, 70.0f / 1024.0f, 70.0f / 1024.0f, 2.0f, 0.0f);
	SpriteBase blockSprite2 = SpriteBase(blocktype2, 0.0f / 1024.0f, 0.0f / 1024.0f, 70.0f / 1024.0f, 70.0f / 1024.0f, 2.0f, 0.0f);
	SpriteBase playerSprite = SpriteBase(textureID2, 0.0f / 1024.0f, 0.0f / 1024.0f, 70.0f / 1024.0f, 70.0f / 1024.0f, 2.0f, 0.0f);
	for (int i = -10; i < 11; i++){
		platformEntities.push_back(new PlatformerEntity(blockSprite, i*blockSprite.getWidth() , -1.0f + blockSprite.getHeight()/2));
	}
	for (size_t i = 0; i < 14; i++){
		platformEntities.push_back(new PlatformerEntity(blockSprite2, -1.333f + blockSprite2.getWidth() / 2,  -1.0f + 1.5* blockSprite2.getHeight() + blockSprite2.getHeight()*i ));
	}
	for (size_t i = 0; i < 14; i++){
		platformEntities.push_back(new PlatformerEntity(blockSprite2, 1.333f - blockSprite2.getWidth() / 2, -1.0f + 1.5* blockSprite2.getHeight() + blockSprite2.getHeight()*i ));
	}
	for (size_t i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->setStatic();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
	}
	player = new PlatformerEntity(playerSprite, 0.0f, 0.0f);
	


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
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_A]){
		player->Left();
	}
	else if (keys[SDL_SCANCODE_D]){
		player->Right();
	}
	if (keys[SDL_SCANCODE_LEFT]){
		//player->Left();
	}
	else if (keys[SDL_SCANCODE_RIGHT]){
		//player->Right();
	}
	if (keys[SDL_SCANCODE_W]){
		player->Up();
	}
	if (keys[SDL_SCANCODE_SPACE]){
		//player->Shoot();
	}
}

void StateGameLevel::Update(float elapsed){
	/*
	for (int i = 0; i < bullets.size(); i++){
		if (!bullets[i]->isEnabled()){
			delete bullets[i];
			bullets.erase(bullets.begin()+i);
		}
	}
	timeElapsed += elapsed;
	if (timeElapsed > 1.0 / bulletsPerSecond){
		timeElapsed = 0.0;
		if (bullets.size() < 10){
			int index = std::rand() % 11; 
			
			size_t maxLoop = 6;
			size_t currentLoop = 0;

			while (!enemies[index]->isEnabled() && currentLoop < maxLoop){
				index += 11;
				if (index > enemies.size() -  1){
					index = std::rand() % 11;
				}
				currentLoop++;
			}
			if (enemies[index]->isEnabled()){
				const array<float, 4> enemyRect = enemies[index]->getRect();
				Bullet *bullet = new Bullet(*bSprite, enemyRect[0], enemyRect[1]);
				bullet->Shoot(enemyRect[0], enemyRect[1], -1.0);
				bullets.push_back(bullet);
			}
		}
	}
	const array<float, 4> rightWall = { 1.33f, 0.0f, 0.1, 2.0 };
	const array<float, 4> leftWall = { -1.33f, 0.0f, 0.1, 2.0 };
	const array<float, 4> topWall = { 0.0f, 1.1f, 2.66, 0.1 };
	const array<float, 4> botWall = { 0.0f, -1.1f, 2.66, 0.1 };
	const array<float, 4> playerBulletRect = playerBullet->getRect();
	const array<float, 4> playerRect = player->getRect();

	vector<const array<float, 4>> enemyRects = getRects(enemies);
	vector<const array<float, 4>> bulletRects = getRects(bullets);

	//Player Wall Collision
	if (hasCollided(playerRect, rightWall)){
		player->Stop();
	}
	if (hasCollided(playerRect, leftWall)){
		player->Stop();
	}
	
	//Enemies Wall Collision
	bool enemiesTouchWall = false;
	for (int i = 0; i < enemies.size() && !enemiesTouchWall; i++){
		if (enemies[i]->isEnabled()){
			if (hasCollided(enemyRects[i], rightWall) || hasCollided(enemyRects[i], leftWall)){
				enemiesTouchWall = true;
			}
		}
	}
	if (enemiesTouchWall){
		for (int i = 0; i < enemies.size(); i++){
			if (enemies[i]->isEnabled()){
				enemies[i]->Move();
			}
		}
	}

	//Bullets Wall Collision
	for (int i = 0; i < bullets.size(); i++){
		if (bullets[i]->isEnabled()){
			if (hasCollided(bulletRects[i], botWall)){
				bullets[i]->disable();
			}
		}
	}

	//Enemy Player Collision
	bool enemyTouchPlayer = false;
	for (int i = 0; i < enemies.size() && !enemyTouchPlayer; i++){
		if (enemies[i]->isEnabled()){
			if (hasCollided(enemyRects[i], playerRect)){
				enemyTouchPlayer = true;
			}
		}
	}
	if (enemyTouchPlayer){
		done = true;
		nextState = STATE_GAME_OVER;
	}

	//Bullet Player Collision
	bool bulletTouchPlayer = false;
	for (int i = 0; i < bullets.size() && !bulletTouchPlayer; i++){
		if (bullets[i]->isEnabled()){
			if (hasCollided(playerRect, bulletRects[i])){
				bulletTouchPlayer = true;
				bullets[i]->disable();
			}
		}
	}
	if (bulletTouchPlayer){
		done = true;
		nextState = STATE_GAME_OVER;
	}

	// playerBullet - Wall, Enemies
	if (playerBullet->isEnabled()){
		if (hasCollided(playerBulletRect, topWall)){
			playerBullet->disable();
		}

		for (int i = 0; i < enemies.size(); i++){
			if (enemies[i]->isEnabled()){
				if (hasCollided(playerBulletRect, enemyRects[i])){
					playerBullet->disable();
					enemies[i]->disable();
					score += enemies[i]->getScore();
					break;
				}
			}
		}

	}

	//Movement
	player->Update(elapsed);
	for (int i = 0; i < enemies.size(); i++){
		enemies[i]->Update(elapsed);
	}
	for (int i = 0; i < bullets.size(); i++){
		bullets[i]->Update(elapsed);
	}
	for (int i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->Update(elapsed);
	}
	*/
	for (int i = 0; i < platformEntities.size(); i++){
		platformEntities[i]->Update(elapsed);
	}
	player->Update(elapsed);
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