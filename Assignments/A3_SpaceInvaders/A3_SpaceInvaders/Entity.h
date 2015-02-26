#pragma once
#include <array>

#include "EntityBase.h"
//#include "SpriteBase.h"

template <typename T>
class Entity : public EntityBase
{
public:
	Entity(T &sprite, float x, float y);
	~Entity();

	void Update(float elapsed); 
	void Render(float elapsed);
	const std::array<float, 4> & getRect() const;

	float lerp(float v0, float v1, float t) { return (1.0 - t)*v0 + t*v1; }
private:
	T sprite;
};

template <typename T>
Entity<T>::Entity<T>(T &sprite, float x, float y)
	: EntityBase(x, y), sprite(sprite)
{

}


template <typename T>
Entity<T>::~Entity<T>(){

}


template <typename T>
void Entity<T>::Update(float elapsed){
	xVelocity = lerp(xVelocity, 0.0f, elapsed * 5.0f);    
	yVelocity = lerp(yVelocity, 0.0f, elapsed * 5.0f);

	xVelocity += xAcceleration * elapsed;
	yVelocity += yAcceleration * elapsed;

	EntityBase::Update(elapsed);
}

template <typename T>
void Entity<T>::Render(float elapsed){
	if (enabled){
		sprite.Draw(elapsed, x, y);
	}
}

template <typename T>
const std::array<float, 4>& Entity<T>::getRect() const{
	return{ x, y, sprite.getWidth(), sprite.getHeight() };
}

