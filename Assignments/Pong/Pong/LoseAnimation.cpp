#include "LoseAnimation.h"

LoseAnimation::LoseAnimation(float x, float y, float rotation, float width, float height, char *image_path):
x(x), y(y), rotation(rotation), width(width), height(height), index(0), image_path(image_path), done(false){
	Update();
}

LoseAnimation::~LoseAnimation(){
}

void LoseAnimation::LoadTexture(const char *image_path){
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

void LoseAnimation::Update(){
	std::string full_path = image_path + std::to_string(index)+".png";
	LoadTexture(full_path.c_str());
	if (index == 24){
		index = 0;
		done = true;
	}
	else{ index++; }
}

void LoseAnimation::Draw(){
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
