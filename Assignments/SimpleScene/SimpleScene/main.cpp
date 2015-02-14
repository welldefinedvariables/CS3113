
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <stdio.h>

SDL_Window* displayWindow;

typedef struct { float x; float y; float r; float g; float b; } Vertex2D;

GLuint LoadTexture(const char *image_path){
	SDL_Surface *surface = IMG_Load(image_path);

	//Generates a new OpenGL texture ID
	GLuint textureID;
	glGenTextures(1, &textureID);

	//Binds a texture to a texture target
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Sets texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);
	return textureID;
}

void DrawSprite(GLint texture, float x, float y, float rotation){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	GLfloat quad[] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	

	//Sets the clear color of the screen
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);


	//Defines an array of vertex triangle data
	Vertex2D triangle[3] = { { 0.0, 0.5, 1.0, 0.0, 0.0 }, 
	{ -0.5, -0.5, 0.0, 1.0, 0.0 }, { 0.5, -0.5, 0.0, 0.0, 1.0 } };

	//Defines an array of vertex square data
	Vertex2D square[4] = { { 1.0, 0.2, 0.0, 1.0, 0.0 }, { -1.0, 0.2, 1.0, 1.0, 0.0 }, { -1.0, -0.2, 0.0, 0.0, 1.0 }, { 1.0, -0.2, 1.0, 0.0, 0.0 } };

	//Load textures
	GLuint cactusTexture = LoadTexture("cactus.png");
	GLuint medalTexture = LoadTexture("flat_medal7.png");
	GLuint planeTexture = LoadTexture("planeBlue1.png");
	
	//Time
	float lastFrameTicks = 0.0f;
	float cactusX = 0.0f;
	float cactusAngle = 0.0f;

	bool done = false;
	
	SDL_Event event;
	
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
		//Clears the screen to the set color
		glClear(GL_COLOR_BUFFER_BIT);
		
		//
		glLoadIdentity();
		glTranslatef(0.0, 0.3, 0.0);
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, triangle);
		glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &triangle[0].r);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		//Renders previously defined arrays
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		//
		glLoadIdentity();
		glTranslatef(0.0, 0.8, 0.0);
		glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, square);
		glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &square[0].r);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		//Renders previously defined arrays
		glDrawArrays(GL_QUADS, 0, 4);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		//
		
		DrawSprite(medalTexture, 0.5, 0.0, 0.0);
		DrawSprite(planeTexture, -0.5, -0.5, 79.0);
		
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		cactusX = fmod(ticks, 2.2f) - 1.1f;
		cactusAngle = fmod(ticks, 5.0f) - 2.5f;

		DrawSprite(cactusTexture, cactusX, 0.5, 180.0 + cactusAngle);

		SDL_GL_SwapWindow(displayWindow);
		
	}

	SDL_Quit();
	return 0;
}