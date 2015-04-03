#pragma once
#include <array>

#include "PlatformerEntityBase.h"
#include "SpriteBase.h"

class PlatformerEntity : public PlatformerEntityBase
{
public:
	PlatformerEntity(SpriteBase &sprite, float x, float y);
	~PlatformerEntity();

	void Update(float elapsed);
	void Render(float elapsed);
	const std::array<float, 4> getRect() const;


protected:
	SpriteBase sprite;
};

