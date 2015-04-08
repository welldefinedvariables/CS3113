#pragma once
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <array>

class DrawHelper{
public:
	float scaleX;
	float scaleY;
	float rotation;
	float r;
	float g;
	float b;
	float a;

	DrawHelper() :
		//x(0.0f), y(0.0f),
		scaleX(1.0f), scaleY(1.0f),
		rotation(0.0),
		r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{};
	//void moveXY(float x, float y) { this->x = x; this->y = y; }
	void scale(float scale) { this->scaleX = scale;  this->scaleY = scale; }
	void scale(float scaleX, float scaleY) { this->scaleX = scaleX; this->scaleY = scaleY; }
	void rotate(float rotate) { this->rotation = rotate; }
	void tintRGB(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
	void tintRGBA(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }

private:

};

/*
void Draw(const DrawHelper &dh, const std::array<float, 4> rect, int spriteTexture, float u, float v){
	// our regular sprite drawing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteTexture);
	glMatrixMode(GL_MODELVIEW);

	float x = rect[0];
	float y = rect[1];
	float width = rect[2];
	float height = rect[3];

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(dh.rotation, 0.0, 0.0, 1.0);
	glScalef(dh.scaleX, dh.scaleY, 1.0);

	GLfloat quad[] = { -width / 2 * dh.scaleX, height / 2 * dh.scaleY,
		-width / 2 * dh.scaleX, -height / 2 * dh.scaleY,
		width / 2 * dh.scaleX, -height / 2 * dh.scaleY,
		width / 2 * dh.scaleX, height / 2 * dh.scaleY };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { u, v,
		u, v + height,
		u + width, v + height,
		u + width, v };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glColor4f(dh.r, dh.g, dh.b, dh.a);
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


void DrawSpriteSheetSprite(const DrawSpriteHelper &dh, const std::array<float, 4> rect, int spriteTexture, int index, int spriteCountX, int
	spriteCountY) {
	
	// our regular sprite drawing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteTexture);
	glMatrixMode(GL_MODELVIEW);

	float x = rect[0];
	float y = rect[1];
	float width = rect[2];
	float height = rect[3];

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(dh.rotation, 0.0, 0.0, 1.0);
	glScalef(dh.scaleX, dh.scaleY, 1.0);

	GLfloat quad[] = { -width / 2 * dh.scaleX, height / 2 * dh.scaleY,
		-width / 2 * dh.scaleX, -height / 2 * dh.scaleY,
		width / 2 * dh.scaleX, -height / 2 * dh.scaleY,
		width / 2 * dh.scaleX, height / 2 * dh.scaleY };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	float u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
	float v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;
	float spriteWidth = 1.0 / (float)spriteCountX;
	float spriteHeight = 1.0 / (float)spriteCountY;
	GLfloat quadUVs[] = { u, v,
		u, v + spriteHeight,
		u + spriteWidth, v + spriteHeight,
		u + spriteWidth, v
	};

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	

	glColor4f(dh.r, dh.g, dh.b, dh.a);
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
*/