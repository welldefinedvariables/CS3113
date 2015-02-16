#ifndef LOSEANIMATION_H
#define LOSEANIMATION_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <string>


class LoseAnimation{
public:
	LoseAnimation(float x, float y, float rotation, float width, float height, char *image_path);
	~LoseAnimation();

	void LoadTexture(const char *image_path);
	void Update();
	void Draw();

	bool done;
private:
	float x;
	float y;
	float rotation;

	GLuint textureID;
	char *image_path;
	int index;

	float width;
	float height;
};

#endif