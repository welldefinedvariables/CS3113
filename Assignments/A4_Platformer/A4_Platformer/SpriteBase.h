#pragma once
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Utility.h"

using namespace Utility;

class SpriteBase{
public:
	SpriteBase(unsigned int textureID);
	SpriteBase(unsigned int textureID, float u, float v, float width, float height);
	SpriteBase(unsigned int textureID, size_t index, size_t spriteCountX, size_t spriteCountY);

	~SpriteBase();
	void Draw(float x, float y);

	void scale(float scale) { this->scaleX = scale;  this->scaleY = scale; }
	void scaleXY(float scaleX, float scaleY) { this->scaleX = scaleX; this->scaleY = scaleY; }
	void rotate(float rotation) { this->rotation = rotation; }
	void tintRGB(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
	void tintRGBA(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }

	void alignQuadCenter(){
		this->quad[0] = -width / 2;
		this->quad[1] = height / 2;
		this->quad[2] = -width / 2;
		this->quad[3] = -height / 2;
		this->quad[4] = width / 2;
		this->quad[5] = -height / 2;
		this->quad[6] = width / 2;
		this->quad[7] = height / 2;
	}
	void alignQuadBottomRight(){
		this->quad[0] = -width;
		this->quad[1] = height;
		this->quad[2] = -width;
		this->quad[3] = 0.0f;
		this->quad[4] = 0;
		this->quad[5] = 0;
		this->quad[6] = 0;
		this->quad[7] = height;
	}

	void setAlignQuadBottomRight(){
		alignCenter = false;
	}
	float getWidth() const { return width * scaleX; }
	float getHeight() const { 
		return height * scaleY; 
	}

protected:
	GLuint textureID;

	GLfloat quad[8];

	bool alignCenter;

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