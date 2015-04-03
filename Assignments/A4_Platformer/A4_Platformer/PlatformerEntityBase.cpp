#include "PlatformerEntityBase.h"

PlatformerEntityBase::PlatformerEntityBase(float x, float y) :EntityBase(x, y), mass(0.0f), 
isStatic(false), collidedTop(false), collidedBottom(false), collidedLeft(false), collidedRight(false)
{
	yAcceleration =-1.0f;
}



PlatformerEntityBase::~PlatformerEntityBase(){}

void PlatformerEntityBase::Update(float elapsed){
	if (enabled){
		xVelocity = lerp(xVelocity, 0.0f, elapsed * xFriction);
		yVelocity = lerp(yVelocity, 0.0f, elapsed * yFriction);

		if (isStatic == false){
			xVelocity += xAcceleration * elapsed;
			yVelocity += yAcceleration * elapsed;
		}
		x += xVelocity * elapsed;
		y += yVelocity * elapsed;
		
	}
}

void PlatformerEntityBase::isColliding(float x, float y, float width, float height){
	std::array<float, 4> rect = getRect();
	float xPenetration = (rect[2] + width) - (rect[0] + x);
	float yPenetration = (rect[3] + height) - (rect[1] + y);
	if (xPenetration > 0.0f){
		if (xVelocity > 0.0f){
			collidedRight = true;
			this->x -= xPenetration;
		}
		else {
			collidedLeft = true;
			this->x += xPenetration;
		}
	}
	if (yPenetration > 0.0f){
		if (yVelocity > 0.0f){
			collidedTop = true;
			this->y -= yPenetration;
		}
		else {
			collidedBottom = true;
			this->y += yPenetration;
		}
	}

 
}

void PlatformerEntityBase::setStatic(){
	isStatic = true;
}

void PlatformerEntityBase::Left(){
	xAcceleration = -2.75;
}
void PlatformerEntityBase::Right(){
	xAcceleration = 2.75;
}
void PlatformerEntityBase::Up(){
	yVelocity = 0.2;
}
void PlatformerEntityBase::Down(){
	yVelocity = -0.2;
}


void PlatformerEntityBase::disable(){
	enabled = false;
}