#pragma once
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteSheet{
public:
	SpriteSheet(const char *image_path);
	~SpriteSheet();
	

	void LoadTexture(const char *image_path);

	void DrawSprite(float x, float y, float u, float v, float width, float height, float rotation, float scale);
private:
	GLuint textureID;
};