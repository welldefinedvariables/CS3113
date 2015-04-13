#pragma once
#include <array>

#include "PlatformerEntityBase.h"
#include "AnimatedSprite.h"

class PlatformerEntity : public PlatformerEntityBase
{
public:
	PlatformerEntity(AnimatedSprite &sprite, float x, float y);
	~PlatformerEntity();

	void Update(float elapsed);
	void Render(float elapsed);
	const std::array<float, 4> getRect() const;


protected:
	AnimatedSprite sprite;
};

