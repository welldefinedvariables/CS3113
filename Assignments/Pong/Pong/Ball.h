#ifndef BALL_H
#define BALL_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>
#include <math.h>

using std::array;

class Ball{
public:
	Ball(float x, float y, float rotation, float width, float height, char *image_path);
	~Ball();

	void LoadTexture(const char *image_path);
	void Update(float elapsed);
	void Draw();

	
	///<summary>Obtains the collision rectangle of Ball {x, y, width, height}</summary>
	const array<float, 4>& getRect() const;
	void hitTop();
	void hitBot();
	void hitLeft(float hitAngle, float spin);
	void hitRight(float hitAngle, float spin);
	void reset();

private:
	float x;
	float y;
	float rotation;

	GLuint textureID;

	float width;
	float height;

	float xVelocity;
	float yVelocity;

	float xAcceleration;
	float yAcceleration;
};

#endif