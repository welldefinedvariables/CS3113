#ifndef LOSEANIMATION_H
#define LOSEANIMATION_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <string>
#include <array>

using std::array;

class LoseAnimation{
public:
	LoseAnimation(float x, float y, float rotation, float width, float height, char *image_path);
	~LoseAnimation();

	void LoadTexture(const char *image_path);
	void Update(float ticks);
	void Draw();

	void Move(float x, float y, float startTime);
	bool done;
private:
	float x;
	float y;
	float rotation;

	float startTime;
	array<GLuint,25> textureIDs;
	GLuint textureID;
	int index;

	float width;
	float height;
};

#endif