#include "Ball.h"

Ball::Ball(float x, float y, float rotation, 
	float width, float height, char *image_path)
	:x(x), y(y), rotation(rotation), 
	width(width), height(height), xVelocity(0.0f), yVelocity(0.0f),
	xAcceleration(0.0f), yAcceleration(0.0f){
	
	LoadTexture(image_path);
}

Ball::~Ball(){}

void Ball::LoadTexture(const char *image_path){
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

void Ball::Update(float elapsed){
	x += xVelocity * elapsed;
	y += yVelocity * elapsed;
	xVelocity += xAcceleration * elapsed;
	yVelocity += yAcceleration * elapsed;
	
	rotation += 5.0f;
}

void Ball::Draw(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);

	GLfloat square[] = { -width/2, height/2, -width/2, -height/2, width/2, -height/2, width/2, height/2};
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


const array<float, 4>& Ball::getRect() const{
	return { x, y, width, height };
}


//Play around
void Ball::hitTop(){
	yVelocity = -abs(yVelocity);
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}

void Ball::hitBot(){
	yVelocity = abs(yVelocity);
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}

void Ball::hitLeft(float hitAngle, float spin){
	xVelocity = 1.5f;
	yVelocity = 1.5f*pow(abs(hitAngle), 0.5f)*hitAngle;
	xAcceleration = -0.8f * abs(spin);
	yAcceleration = 4.0f * spin;
}

void Ball::hitRight(float hitAngle, float spin){
	xVelocity = -1.5f;
	yVelocity = 1.5f*pow(abs(hitAngle),0.5f)*hitAngle;
	xAcceleration = 0.8f * abs(spin);
	yAcceleration = 4.0f * spin;
}

void Ball::reset(){
	x = 0.0f;
	y = 0.0f;
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}