
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>
#include <math.h>

#include "Ball.h"
#include "Paddle.h"

#define ORTHOTOP 1.0f
#define ORTHOBOT -1.0f
#define ORTHOLEFT -1.33f
#define ORTHORIGHT 1.33f

using std::array;

SDL_Window* displayWindow;
SDL_Joystick* playerOneController;
Ball* ball;
Paddle* paddle;
Paddle* paddle2;

bool hasCollided(const array<float, 4> &rect1, const array<float, 4> &rect2){
	return (abs(rect1[0] - rect2[0]) <= (rect1[2] + rect2[2]) / 2 &&
		abs(rect1[1] - rect2[1]) <= (rect1[3] + rect2[3]) / 2);
}

void HandleCollisions(){
	//Collision Rectangles
	const array<float, 4> ballRect = ball->getRect();
	const array<float, 4> paddleRect = paddle->getRect();
	const array<float, 4> paddle2Rect = paddle2->getRect();

	//x y, width, height 
	//Top
	if (ballRect[1] + ballRect[3]/2 >= ORTHOTOP ){
		ball->hitTop();
	}

	//Bottom
	if (ballRect[1] - ballRect[3]/2 <= ORTHOBOT ){
		ball->hitTop();
	}

	//Left
	if (ballRect[0] - ballRect[2] / 2 >= ORTHORIGHT){
		ball->hitLeft();
	}

	//Right
	if (ballRect[0] + ballRect[2] / 2 <= ORTHOLEFT){
		ball->hitLeft();
	}
	//Paddle 1
	if (abs(ballRect[0] - paddleRect[0]) <= ( ballRect[2]+paddleRect[2] )/2 &&
		abs(ballRect[1] - paddleRect[1]) <= (ballRect[3] + paddleRect[3]) / 2){
		ball->hitLeft();
	}

	//Paddle 2
	if (hasCollided(ballRect, paddle2Rect)){
		ball->hitLeft();
	}
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
	paddle = new Paddle(-1.3f, 0.0f, 0.0f, 0.050f, 0.28f, "laserGreen12.png");
	paddle2 = new Paddle(1.3f, 0.0f, 0.0f, 0.050f, 0.28f, "laserRed12.png");
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
	paddle->Draw();
	paddle2->Draw();


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