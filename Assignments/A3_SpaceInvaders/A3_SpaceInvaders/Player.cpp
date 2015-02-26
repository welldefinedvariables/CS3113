#include "Player.h"

Player::Player(SpriteBase sprite, float x, float y) :Entity<SpriteBase>(sprite, x, y){

}

void Player::Update(float elapsed){
	xAcceleration = lerp(xAcceleration, 0.0f, elapsed * 3.0f);
	yAcceleration = lerp(yAcceleration, 0.0f, elapsed * 3.0f);

	Entity::Update(elapsed);
}

void Player::Render(float elapsed){
	Entity::Render(elapsed);
}

void Player::Left(){
	xAcceleration = -4.0;
}
void Player::Right(){
	xAcceleration = 4.0;
}