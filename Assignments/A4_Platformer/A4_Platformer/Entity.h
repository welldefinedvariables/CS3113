#pragma once
#include <array>

#include "EntityBase.h"


template <typename T>
class Entity : public EntityBase
{
public:
	Entity(T &sprite, float x, float y);
	~Entity();

	void Update(float elapsed); 
	void Render(float elapsed);
	const std::array<float, 4> getRect() const;

	
protected:
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
	EntityBase::Update(elapsed);
}

template <typename T>
void Entity<T>::Render(float elapsed){
	if (enabled){
		sprite.Draw(x, y);
	}
}

template <typename T>
const std::array<float, 4> Entity<T>::getRect() const{
	return{ x, y, sprite.getWidth(), sprite.getHeight() };
}

