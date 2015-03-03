#include "Bullet.h"

Bullet::Bullet(SpriteBase sprite, float x, float y) : Entity<SpriteBase>(sprite, x, y){
	enabled = false;
}

void Bullet::Update(float elapsed){

	Entity::Update(elapsed);
}

void Bullet::Render(float elapsed){
	if (enabled){
		sprite.DrawRGBA(elapsed, x, y, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0);
	}
}

void Bullet::Shoot(float x, float y, float direction){
	if (!enabled){
		this->x = x;
		this->y = y;
		yAcceleration =  6.0f * direction; 
		enabled = true;
	}
}

void Bullet::disable(){
	enabled = false;
}