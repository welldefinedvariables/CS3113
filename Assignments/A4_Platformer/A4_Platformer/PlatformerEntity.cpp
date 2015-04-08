#include "PlatformerEntity.h"


PlatformerEntity::PlatformerEntity(SpriteBase &sprite, float x, float y)
	: PlatformerEntityBase(x, y), sprite(sprite)
{

}


PlatformerEntity::~PlatformerEntity(){

}

void PlatformerEntity::Update(float elapsed){
	PlatformerEntityBase::Update(elapsed);
}

void PlatformerEntity::Render(float elapsed){
	if (enabled){
		sprite.Draw(x, y);
	}
}

const std::array<float, 4> PlatformerEntity::getRect() const{
	return{ this->x, this->y, sprite.getWidth(), sprite.getHeight() };
}
