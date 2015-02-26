#include "EntityBase.h"

EntityBase::EntityBase(float x, float y) :
x(x), y(y), xVelocity(0.0f), yVelocity(0.0f), xAcceleration(0.0f), yAcceleration(0.0f), enabled(true)
{

}

EntityBase::~EntityBase(){

}

void EntityBase::Update(float elapsed){
	x += xVelocity * elapsed;
	y += yVelocity * elapsed;
}
