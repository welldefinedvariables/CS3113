#include "EntityBase.h"

EntityBase::EntityBase(float x, float y) :
x(x), y(y), xVelocity(0.0f), yVelocity(0.0f), xAcceleration(0.0f), yAcceleration(0.0f), enabled(true)
{

}

EntityBase::~EntityBase(){

}

void EntityBase::Update(float elapsed){
	xVelocity = lerp(xVelocity, 0.0f, elapsed * 5.0f);
	yVelocity = lerp(yVelocity, 0.0f, elapsed * 5.0f);

	xVelocity += xAcceleration * elapsed;
	yVelocity += yAcceleration * elapsed;

	x += xVelocity * elapsed;
	y += yVelocity * elapsed;
}
