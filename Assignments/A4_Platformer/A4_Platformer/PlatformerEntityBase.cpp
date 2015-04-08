#include "PlatformerEntityBase.h"

PlatformerEntityBase::PlatformerEntityBase(float x, float y) :EntityBase(x, y), mass(0.0f), 
isStatic(false), collidedTop(false), collidedBottom(false), collidedLeft(false), collidedRight(false)
{
	yAcceleration = 0.0f;
	xFriction = 1.5f;
	yFriction = 0.0f;
}



PlatformerEntityBase::~PlatformerEntityBase(){}

void PlatformerEntityBase::Update(float elapsed){
	if (enabled){
		xVelocity = lerp(xVelocity, 0.0f, elapsed * xFriction);
		yVelocity = lerp(yVelocity, 0.0f, elapsed * yFriction);

		if (isStatic == false){
			xVelocity += 0.0f * elapsed; //xGravity
			yVelocity += -9.8 * elapsed; //yGravity

			xVelocity += xAcceleration * elapsed;
			yVelocity += yAcceleration * elapsed;
		}

		x += xVelocity * elapsed;
		y += yVelocity * elapsed;
	
	}
}

void PlatformerEntityBase::UpdateX(float elapsed){
	if (enabled){
		if (collidedBottom){
			xVelocity = lerp(xVelocity, 0.0f, elapsed * xFriction);
		}
		if (isStatic == false){
			xVelocity += 0.0f * elapsed; //xGravity
			xVelocity += xAcceleration * elapsed;
		}
		x += xVelocity * elapsed;
	}
}

void PlatformerEntityBase::UpdateY(float elapsed){
	if (enabled){
		if (collidedLeft || collidedRight){
			yVelocity = lerp(yVelocity, 0.0f, elapsed * yFriction);
		}
		if (isStatic == false){
			yVelocity += -9.8 * elapsed; //yGravity
			yVelocity += yAcceleration * elapsed;
		}
		y += yVelocity * elapsed;
	}
}

bool PlatformerEntityBase::isColliding(const std::array<float, 4> &rect, const std::array<float, 4> &rect2){
	return rect[0] < (rect2[0] + rect2[2]) &&
		(rect[0] + rect[2]) > rect2[0] &&
		rect[1] < (rect2[1] + rect2[3]) &&
		(rect[1] + rect[3]) > rect2[1];
}

void PlatformerEntityBase::CollideX(const std::array<float, 4> &rect2){
	const std::array<float, 4> rect1 = this->getRect();
	if (isColliding(rect1, rect2)){
		float xDistance = fabs(rect1[0] - rect2[0]);
		float xOverlap = fabs(xDistance - (rect1[2] + rect2[2]) / 2);
		if (rect1[0] < rect2[0]){
			collidedRight = true;
			x -= xOverlap;
		}
		else{
			collidedLeft = true;
			x += xOverlap;
		}
	}
}

void PlatformerEntityBase::CollideY(const std::array<float, 4> &rect2){
	const std::array<float, 4> rect1 = this->getRect();
	if (isColliding(rect1, rect2)){
		float yDistance = fabs(rect1[1] - rect2[1]);
		float yOverlap = fabs(yDistance - (rect1[3] + rect2[3]) / 2);
		if (rect1[1] < rect2[1]){
			collidedTop = true;
			y -= yOverlap;
		}
		else{
			collidedBottom = true;
			y += yOverlap;
		}
	}
}

void PlatformerEntityBase::ResetCollide(){
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	collidedTop = false;
}

void PlatformerEntityBase::HandleCollision(float elapsed){
	if (collidedBottom){
		yAcceleration = 0.0;
		yVelocity = 0.0;
	}
	if (collidedTop){
		yAcceleration = 0.0;
		yVelocity = 0.0;
	}
	if (collidedLeft){
		xAcceleration = 0.0;
		xVelocity = 0.0;
	}
	if (collidedRight){
		xAcceleration = 0.0;
		xVelocity = 0.0;
	}
}



void PlatformerEntityBase::setStatic(){
	isStatic = true;
}

void PlatformerEntityBase::Left(){
	xAcceleration = -2.0;
}
void PlatformerEntityBase::Right(){
	xAcceleration = 2.0;
}
void PlatformerEntityBase::Up(){
	if (collidedBottom){
		yVelocity = 2.0;
	}
}
void PlatformerEntityBase::Down(){
	yVelocity = -1.0;
}

void PlatformerEntityBase::StopLR(){
	xAcceleration = 0.0f;
	if (collidedBottom){
		xVelocity = 0.0f;
	}
}


void PlatformerEntityBase::disable(){
	enabled = false;
}