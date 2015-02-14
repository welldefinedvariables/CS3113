
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>

#include "Ball.h"

#define ORTHOTOP 1.0f
#define ORTHOBOT -1.0f
#define ORTHOLEFT -1.33f
#define ORTHORIGHT 1.33f

using std::array;

SDL_Window* displayWindow;
SDL_Joystick* playerOneController;
Ball* ball;

void HandleCollisions(){
	//Collision Rectangles
	const array<float, 4> ballRect = ball->getRect();

	//x y, width, height 
	//Top
	if (ballRect[1] + ballRect[3]/2 > ORTHOTOP ){
		ball->hitTop();
	}

	//Bottom
	if (ballRect[1] - ballRect[3]/2 < ORTHOBOT ){
		ball->hitTop();
	}

	//Left
	if (ballRect[0] - ballRect[2] / 2 > ORTHORIGHT){
		ball->hitLeft();
	}

	//Right
	if (ballRect[0] + ballRect[2] / 2 < ORTHOLEFT){
		ball->hitLeft();
	}
	//Paddle 1

	//Paddle 2
}

void Setup(){
	//Setup SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	playerOneController = SDL_JoystickOpen(0);

	//Setup OpenGL
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	//Setup Projection Matrix
	
	//Setup Entities
	//border=1.28,0.95 if width&height = 0.1
	ball = new Ball(0.0f, 0.0f, 0.0f, 0.05f, 0.05f, "ballBlue.png");
}

void ProcessEvents(bool& done){
	//SDL event loop
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		//Check Input Events

		//Exit
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		//Mouse
		else if (event.type == SDL_MOUSEMOTION){

		}
		else if (event.type == SDL_MOUSEBUTTONDOWN){

		}
		//Controller
		else if (event.type == SDL_JOYAXISMOTION){

		}
		else if (event.type == SDL_JOYBUTTONDOWN){

		}
		//Keyboard

	}
}

void Update(){
	//Physics
	
	//Movements
	ball->Update();
	
	//Collisions
	HandleCollisions();
}

void Render(){
	//Clears the screen to the set color
	glClear(GL_COLOR_BUFFER_BIT);

	//Setup Transforms Draw 
	ball->Draw();


	SDL_GL_SwapWindow(displayWindow);
}

void CleanUp(){
	SDL_JoystickClose(playerOneController);
}

int main(int argc, char *argv[])
{
	Setup();
	
	bool done = false;
	
	//SDL_Event event;

	while (!done) {
		
		ProcessEvents(done);
		Update();
		Render();
		
	}

	CleanUp();
	SDL_Quit();
	return 0;
}