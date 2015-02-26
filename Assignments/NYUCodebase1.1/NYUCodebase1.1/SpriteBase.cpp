#include "SpriteBase.h"

SpriteBase::SpriteBase(unsigned int textureID, float u, float v, float width, float height, float scale, float rotation)
:textureID(textureID), u(u), v(v), width(width), height(height), scale(scale), rotation(rotation){
	
}
SpriteBase::~SpriteBase(){

}

void SpriteBase::Draw(float elapsed, float x, float y){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	glScalef(scale, scale, 1.0);

	GLfloat quad[] = {	-width/2 * scale, height/2 * scale, 
						-width/2 * scale, -height/2 * scale, 
						width/2 * scale, -height/2 * scale, 
						width/2 * scale, height/2 * scale };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);


	GLfloat quadUVs[] = {	u, v, 
							u, v + height, 
							u + width, v + height, 
							u + width, v };

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

float SpriteBase::getWidth() const{
	return width*scale;
}
float SpriteBase::getHeight() const{
	return height*scale;
}