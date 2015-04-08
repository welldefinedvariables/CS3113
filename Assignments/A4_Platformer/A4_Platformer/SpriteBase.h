#pragma once
#include <SDL_opengl.h>
#include <SDL_image.h>


class SpriteBase{
public:
	SpriteBase(unsigned int textureID, float u, float v, float width, float height);
	SpriteBase(unsigned int textureID, size_t index, size_t spriteCountX, size_t spriteCountY);

	~SpriteBase();

	void Draw(float x, float y);

	void setSpriteIndex(size_t index, size_t spriteCountX, size_t spriteCountY);

	void scale(float scale) { this->scaleX = scale;  this->scaleY = scale; }
	void scaleXY(float scaleX, float scaleY) { this->scaleX = scaleX; this->scaleY = scaleY; }
	void rotate(float rotate) { this->rotation = rotate; }
	void tintRGB(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
	void tintRGBA(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }

	float getWidth() const;
	float getHeight() const;

protected:
	GLuint textureID;

	float u;
	float v;

	float width;
	float height;

	float scaleX;
	float scaleY;
	float rotation;

	float r;
	float g;
	float b;
	float a;
};