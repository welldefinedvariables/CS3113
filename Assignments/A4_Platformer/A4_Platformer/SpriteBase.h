#pragma once
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteBase{
public:
	SpriteBase(unsigned int textureID, float u, float v, float width, float height, float scale, float rotation);
	~SpriteBase();

	virtual void Draw(float elapsed, float x, float y);
	virtual void DrawRGBA(float elapsed, float x, float y, float r, float g, float b, float a);
	virtual void DrawRGBA(float elapsed, float x, float y, float scaleX, float scaleY, float r, float g, float b, float a);



	float getWidth() const;
	float getHeight() const;
protected:
	GLuint textureID;

	float u;
	float v;

	float width;
	float height;

	float rotation;
	float scale;
};