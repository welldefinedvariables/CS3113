#include "SpriteBase.h"

SpriteBase::SpriteBase(unsigned int textureID, float u, float v, float width, float height)
:textureID(textureID), u(u), v(v), width(width), height(height), 
scaleX(1.0f), scaleY(1.0f), rotation(0.0f), 
r(1.0f), g(1.0f), b(1.0f), a(1.0f) {
}

SpriteBase::SpriteBase(unsigned int textureID, size_t index, size_t spriteCountX, size_t spriteCountY):
textureID(textureID), scaleX(1.0f), scaleY(1.0f), rotation(0.0f), 
r(1.0f), g(1.0f), b(1.0f), a(1.0f) {
	this->u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
	this->v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;
	this->width = 1.0 / (float)spriteCountX;
	this->height = 1.0 / (float)spriteCountY;
}

SpriteBase::~SpriteBase(){

}

void SpriteBase::Draw(float x, float y){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	glScalef(scaleX, scaleY, 1.0);

	float w = width;
	float h = height;

	GLfloat quad[] = { -w / 2, h / 2,
		-w / 2, -h / 2,
		w / 2, -h / 2,
		w / 2, h / 2 };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { u, v,
		u, v + height,
		u + width, v + height,
		u + width, v };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(r, g, b, a);
	glEnableClientState(GL_COLOR4_BIT_PGI);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR4_BIT_PGI);

	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
}

void SpriteBase::setSpriteIndex(size_t index, size_t spriteCountX, size_t spriteCountY){
	this->u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
	this->v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;
	this->width = 1.0 / (float)spriteCountX;
	this->height = 1.0 / (float)spriteCountY;
}

float SpriteBase::getWidth() const{
	//Coordinates coordinates = convertOpenGLToPixels(width * scaleX, height * scaleY);
	return width * scaleX;
}
float SpriteBase::getHeight() const{
	//Coordinates coordinates = convertOpenGLToPixels(width * scaleX, height * scaleY);
	return height * scaleY;
}