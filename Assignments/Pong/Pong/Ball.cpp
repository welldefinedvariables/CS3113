#include "Ball.h"

Ball::Ball(const float x, const float y, const float rotation, 
	const float width, const float height, const char *image_path)
	:x(x), y(y), rotation(rotation), 
	width(width), height(height), xVelocity(0.0007f), yVelocity(0.0004f),
	xAcceleration(0.00001), yAcceleration(0.000005){
	
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

void Ball::Update(){
	x += xVelocity;
	y += yVelocity;
	xVelocity += xAcceleration;
	yVelocity += yAcceleration;
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

void Ball::hitTop(){
	yVelocity = -yVelocity;
}
void Ball::hitLeft(){
	xVelocity = -xVelocity;
}