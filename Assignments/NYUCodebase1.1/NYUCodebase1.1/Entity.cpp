#include "Entity.h"

template <typename T>
Entity<T>::Entity(T &sprite, float x, float y)
	:EntityBase(x, y), sprite(sprite)
{

}


template <typename T>
Entity<T>::~Entity(){

}


template <typename T>
void Entity<T>::Render(float elapsed){
	if (enabled){
		T->Draw(elapsed, x, y);
	}
}

template <typename T>
const std::array<float, 4>& Entity<T>::getRect() const{
	return{ x, y, sprite->getWidth(), sprite->getHeight() };
}

