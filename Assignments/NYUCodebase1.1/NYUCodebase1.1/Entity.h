#pragma once
#include <array>

#include "SpriteBase.h"

template <typename T>
class Entity : public EntityBase
{
public:
	Entity(T &sprite, float x, float y);
	~Entity();

	void Render(float elapsed);
	const std::array<float, 4> & getRect() const;

private:
	T sprite;
};

