#ifndef BALL_H
#define BALL_H

#include <SDL.h> // Effect?
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>

using std::array;

class Ball{
public:
	Ball(const float x, const float y, const float rotation, const float width, const float height, const char *image_path);
	~Ball();

	void LoadTexture(const char *image_path);
	void Update();
	void Draw();

	
	///<summary>Obtains the collision rectangle of Ball {x, y, width, height}</summary>
	const array<float, 4>& getRect() const;
	void hitTop();
	void hitLeft();

private:
	float x;
	float y;
	float rotation;

	GLuint textureID;

	float width;
	float height;

	float xVelocity;
	float yVelocity;
};

#endif