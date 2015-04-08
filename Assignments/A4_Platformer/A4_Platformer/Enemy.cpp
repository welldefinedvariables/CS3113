#include "Enemy.h"

Enemy::Enemy(SpriteBase sprite, float x, float y, unsigned int score) :Entity<SpriteBase>(sprite, x, y), score(score), xInitial(x), yInitial(y){
	Right();
}

void Enemy::Update(float elapsed){
	if (enabled){
		if (abs(xAcceleration) < 0.25){
			if (xAcceleration > 0){
				xAcceleration += 1.00;
			}
			else { xAcceleration -= 1.00; }
		}

		xAcceleration = lerp(xAcceleration, 0.0f, elapsed * 2.5f);
		Entity::Update(elapsed);
	}
}

void Enemy::Render(float elapsed){
	if (enabled){
		sprite.scaleXY((4.0 - abs(xVelocity)) / 3.0, 1.0);
		sprite.tintRGBA(0.5, 0.5, 0.5, 1.0);
		sprite.Draw(x, y);
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
	xAcceleration = -2.75;
}
void Enemy::Right(){
	xAcceleration = 2.75;
}

unsigned int Enemy::getScore(){
	return score;
}

void Enemy::disable(){
	enabled = false;
}

void Enemy::reset(){
	enabled = true;
	x = xInitial; 
	y = yInitial;
	xVelocity = 0;
	yVelocity = 0;
	xAcceleration = 0;
	Right();
}