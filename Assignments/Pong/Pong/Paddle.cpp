#include "Paddle.h"

Paddle::Paddle(float x, float y, float rotation,
	float width, float height, char *image_path)
	:x(x), y(y), rotation(rotation),
	width(width), height(height), xVelocity(0.0f), yVelocity(0.0f), xAcceleration(0.0f), yAcceleration(0.0f){

	LoadTexture(image_path);
}

Paddle::~Paddle(){}

void Paddle::LoadTexture(const char *image_path){
	SDL_Surface *surface = IMG_Load(image_path);

	//Generates a new OpenGL texture ID
	glGenTextures(1, &textureID);

	//Binds a texture to a texture target
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Sets texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
}

void Paddle::Update(float elapsed){
	y += yVelocity * elapsed;
	yAcceleration *= 0.99;
	//x = yAcceleration / (-1.0f);
}

void Paddle::Draw(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);

	GLfloat square[] = { -width / 2, height / 2, -width / 2, -height / 2, width / 2, -height / 2, width / 2, height / 2 };
	glVertexPointer(2, GL_FLOAT, 0, square);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
}


const array<float, 4>& Paddle::getRect() const{
	return{ x, y, width, height };
}

void Paddle::Up(){
	yVelocity = 1.5f;
	if (yAcceleration == 0.0f)
	{
		yAcceleration = -1.0f;
	}
}

void Paddle::Down(){
	yVelocity = -1.5f;
	if (yAcceleration == 0.0f)
	{
		yAcceleration = 1.0f;
	}
}

void Paddle::Stop(){
	yAcceleration = 0.0f;
	if (yVelocity != 0.0f){
		if (y > 1.0f - height / 2){
			y = 1.0f - height/2;
		}
		else if (y < -1.0f + height / 2){
			y = -1.0f + height/2;
		}
		yVelocity = 0.0f;
	}
}

float Paddle::getSpin() const{
	return yAcceleration;
}