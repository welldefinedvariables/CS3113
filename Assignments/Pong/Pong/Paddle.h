#ifndef PADDLE_H
#define PADDLE_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>

using std::array;

class Paddle{
public:
	Paddle(const float x, const float y, const float rotation, const float width, const float height, const char *image_path);
	~Paddle();

	void LoadTexture(const char *image_path);
	void Update();
	void Draw();


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
};

#endif