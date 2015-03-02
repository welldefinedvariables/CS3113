#include "Player.h"

Player::Player(SpriteBase sprite, float x, float y) :Entity<SpriteBase>(sprite, x, y){

}
Player::Player(SpriteBase sprite, Bullet *bullet, float x, float y):Entity<SpriteBase>(sprite, x, y), bullet(bullet){

}

void Player::Stop(){
	xVelocity = -x*0.1;
}

void Player::Update(float elapsed){
	if (enabled){
		xAcceleration = lerp(xAcceleration, 0.0f, elapsed * 2.0f);
		Entity::Update(elapsed);
		if (bullet != nullptr){
			bullet->Update(elapsed);
		}
	}
}

void Player::Render(float elapsed){
	if (enabled){
		sprite.DrawRGBA(elapsed, x, y, (16.0 - abs(xAcceleration)) / 12.0, 1.0, 1.0, 0.5, 0.5, 1.0);
		if (bullet != nullptr){
			bullet->Render(elapsed);
		}
	}
}

void Player::Left(){
	xAcceleration = -4.0;
}
void Player::Right(){
	xAcceleration = 4.0;
}
void Player::Shoot(){
	bullet->Shoot(x, y, 1.0f);
}

