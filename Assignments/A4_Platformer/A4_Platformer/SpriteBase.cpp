#include "SpriteBase.h"

SpriteBase::SpriteBase(unsigned int textureID) :
	SpriteBase(textureID, 0.0f, 0.0f, 1.0f, 1.0f){
}

SpriteBase::SpriteBase(unsigned int textureID, float u, float v, float width, float height)
:textureID(textureID), u(u), v(v), width(width), height(height), 
scaleX(1.0f), scaleY(1.0f), rotation(0.0f), 
r(1.0f), g(1.0f), b(1.0f), a(1.0f), alignCenter(true) {

}

SpriteBase::SpriteBase(unsigned int textureID, size_t index, size_t spriteCountX, size_t spriteCountY) : SpriteBase(textureID,
	(float)(((int)index) % spriteCountX) / (float)spriteCountX,
	(float)(((int)index) / spriteCountX) / (float)spriteCountY,
	1.0 / (float)spriteCountX,
	1.0 / (float)spriteCountY){

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

	
	/*
	GLfloat quad[] = { -width / 2, height / 2,
		-width / 2, -height / 2,
		width / 2, -height / 2,
		width / 2, height / 2 };
	
	GLfloat quad[] = { -width, height,
		-width, 0.0f,
		0.0f, 0.0f,
		0.0f, height };
	*/

	if (alignCenter){
		alignQuadCenter();
	}
	else{
		alignQuadBottomRight();
	}
	glVertexPointer(2, GL_FLOAT, 0, this->quad);
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

