
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <array>
#include <math.h>

#include "Ball.h"
#include "Paddle.h"
#include "LoseAnimation.h"

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

float lastFrameTicks;

int control1; // 0 = mouse, 1 = keyboard, 2 = controller
int control2;

int playerScore;
int player2Score;

bool newGame;

LoseAnimation* loseAnimation;
bool lose;

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
	if (ballRect[1] + ballRect[3] / 2 >= ORTHOTOP){
		ball->hitTop();
	}
	if (paddleRect[1] + paddleRect[3] / 2 > ORTHOTOP){
		paddle->Stop();
	}
	if (paddle2Rect[1] + paddle2Rect[3] / 2 > ORTHOTOP){
		paddle2->Stop();
	}

	//Bottom
	if (ballRect[1] - ballRect[3] / 2 <= ORTHOBOT){
		ball->hitBot();
	}
	if (paddleRect[1] - paddleRect[3] / 2 < ORTHOBOT){
		paddle->Stop();
	}
	if (paddle2Rect[1] - paddle2Rect[3] / 2 < ORTHOBOT){
		paddle2->Stop();
	}

	//Right
	if (ballRect[0] - ballRect[2] / 2 >= ORTHORIGHT){
		playerScore++;
		lose = true;

		loseAnimation->Move(1.33f, ballRect[1], lastFrameTicks);

		ball->reset();
		ball->hitLeft(0.0f, 0.0f);
	}

	//Left
	if (ballRect[0] + ballRect[2] / 2 <= ORTHOLEFT){
		player2Score++;
		lose = true;

		loseAnimation->Move(-1.33f, ballRect[1], lastFrameTicks);

		ball->reset();
		ball->hitRight(0.0f, 0.0f);
	}
	//Paddle 1
	if (abs(ballRect[0] - paddleRect[0]) <= (ballRect[2] + paddleRect[2]) / 2 &&
		abs(ballRect[1] - paddleRect[1]) <= (ballRect[3] + paddleRect[3]) / 2){
		ball->hitLeft((ballRect[1] - paddleRect[1]) / (paddleRect[3] / 2), paddle->getSpin());
	}

	//Paddle 2
	if (hasCollided(ballRect, paddle2Rect)){
		ball->hitRight((ballRect[1] - paddle2Rect[1]) / (paddle2Rect[3] / 2), paddle2->getSpin());
	}

	//Ai Players

	if (control1 == 4){

		if (ballRect[1] > (paddleRect[1] + paddleRect[3] / 4))
		{
			paddle->Up();
		}
		else if (ballRect[1] < (paddleRect[1] + paddleRect[3] / 4))
		{
			paddle->Down();
		}
		else{
			paddle->Stop();
		}
	}
	if (control2 == 3){
		if ((paddle2Rect[0] - ballRect[0]) < 0.1)
		{
			paddle2->Stop();
		}
		if (ballRect[1] > paddle2Rect[1])
		{
			paddle2->Up();
		}
		else if (ballRect[1] < paddle2Rect[1])
		{
			paddle2->Down();
		}
		else{
			paddle2->Stop();
		}
	}

}

void Setup(){
	//Setup SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	displayWindow = SDL_CreateWindow("PoNg", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
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
	ball = new Ball(0.0f, 0.0f, 0.0f, 0.1f, 0.1f, "ballBlue.png");
	paddle = new Paddle(-1.18f, 0.0f, 0.0f, 0.1f, 0.45f, "laserGreen12.png");
	paddle2 = new Paddle(1.18f, 0.0f, 0.0f, 0.1f, 0.45f, "laserRed12.png");

	loseAnimation = new LoseAnimation(0.0f, 0.0f, 0.0f, 0.3f, 0.3f, "whitePuff");

	lastFrameTicks = 0.0f;

	control1 = 0;
	control2 = 1;

	playerScore = 0;
	player2Score = 0;

	newGame = true;
	lose = false;
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
			if (event.motion.yrel < 0){
				if (control1 == 0){
					paddle->Up();
				}
				if (control2 == 0){
					paddle2->Up();
				}
			}
			else if (event.motion.yrel > 0){
				if (control1 == 0){
					paddle->Down();
				}
				if (control2 == 0){
					paddle2->Down();
				}
			}
			else {
				if (control1 == 0){
					paddle->Stop();
				}
				if (control2 == 0){
					paddle2->Stop();
				}
			}

		}
		else if (event.type == SDL_MOUSEBUTTONDOWN){

		}
		//Controller
		else if (event.type == SDL_JOYAXISMOTION){
			if (event.jaxis.axis == 1)
			{
				if (event.jaxis.value > 0){
					if (control1 == 0){
						paddle->Up();
					}
					if (control2 == 0){
						paddle2->Up();
					}
				}
				else if (event.jaxis.value < 0){
					if (control1 == 0){
						paddle->Stop();
					}
					if (control2 == 0){
						paddle2->Stop();
					}
				}
			}
			else {
				if (control1 == 0){
					paddle->Stop();
				}
				if (control2 == 0){
					paddle2->Stop();
				}
			}
		}
		else if (event.type == SDL_JOYBUTTONDOWN){

		}
		//Keyboard
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.scancode == SDL_SCANCODE_1){
				control1 = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_2){
				control1 = 1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_3){
				control1 = 2;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_4){
				control1 = 4;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_5){
				control2 = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_6){
				control2 = 1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_7){
				control2 = 2;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_8){
				control2 = 3;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_9){
				//control2 = 3;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_0){
				//ball->hitLeft(1.0f,1.0f);
			}

			//Player 1 Keyboard Control
			else {
				if (control1 == 1){
					if (event.key.keysym.scancode == SDL_SCANCODE_W){
						paddle->Up();
					}
					else if (event.key.keysym.scancode == SDL_SCANCODE_S){
						paddle->Down();
					}
				}

				//Player 2 Keyboard Control
				if (control2 == 1){
					if (event.key.keysym.scancode == SDL_SCANCODE_UP){
						paddle2->Up();
					}
					else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
						paddle2->Down();
					}
				}
			}
		}
		else if (event.type == SDL_KEYUP){
			if (control1 == 1){
				if (event.key.keysym.scancode == SDL_SCANCODE_W){
					paddle->Stop();
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_S){
					paddle->Stop();
				}
			}
			if (control2 == 1){
				if (event.key.keysym.scancode == SDL_SCANCODE_UP){
					paddle2->Stop();
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
					paddle2->Stop();
				}
			}
		}

	}
}

void Update(){
	//Physics
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	if (lose && elapsed){
		if (loseAnimation->done)
		{
			lose = false;
		}
		else {
			loseAnimation->Update(ticks);
		}
	}
	//Movements
	ball->Update(elapsed);
	paddle->Update(elapsed);
	paddle2->Update(elapsed);

	if (newGame){
		ball->hitLeft(0.0f, 0.0f);
		newGame = false;
	}

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

	if (lose) {
		loseAnimation->Draw();
	}

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