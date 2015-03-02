#include "Enemy.h"

Enemy::Enemy(SpriteBase sprite, float x, float y, unsigned int score) :Entity<SpriteBase>(sprite, x, y), score(score){
	Right();
}

void Enemy::Update(float elapsed){
	if (enabled){
		xAcceleration = lerp(xAcceleration, 0.0f, elapsed * 0.5f);
		Entity::Update(elapsed);
	}
}

void Enemy::Render(float elapsed){
	if (enabled){
		sprite.DrawRGBA(elapsed, x, y, (16.0 - abs(xAcceleration)) / 12.0, 1.0, 1.0, 0.5, 0.5, 1.0);
	}
}

void Enemy::Move(){
	if (xAcceleration > 0.0){
		Left();
	}
	else{
		Right();
	}
	xVelocity = -xVelocity;
	yVelocity = -0.2;
}

void Enemy::Left(){
	xAcceleration = -1.5;
}
void Enemy::Right(){
	xAcceleration = 1.5;
}

unsigned int Enemy::getScore(){
	return score;
}

void Enemy::disable(){
	enabled = false;
}