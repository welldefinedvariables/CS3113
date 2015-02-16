#ifndef PADDLE_H
#define PADDLE_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>

using std::array;

class Paddle{
public:
	Paddle(float x, float y, float rotation, float width, float height, char *image_path);
	~Paddle();

	void LoadTexture(const char *image_path);
	void Update(float elapsed);
	void Draw();

	void Up();
	void Down();
	void Stop();
	float getSpin() const;

	///<summary>Obtains the collision rectangle of Paddle {x, y, width, height}</summary>
	const array<float, 4>& getRect() const;

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