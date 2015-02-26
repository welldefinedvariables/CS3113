#pragma once
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteBase{
public:
	SpriteBase(unsigned int textureID, float u, float v, float width, float height, float scale, float rotation);
	~SpriteBase();

	virtual void Draw(float elapsed, float x, float y);
	float getWidth() const;
	float getHeight() const;
private:
	GLuint textureID;

	float u;
	float v;

	float width;
	float height;

	float rotation;
	float scale;
};