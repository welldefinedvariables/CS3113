#include "Application.h"

Application::Application(){
	Init();
	done = false;
	lastFrameTicks = 0.0f;
	timeLeftOver = 0.0f;
	mainMenu = StateMainMenu();
	gameLevel = StateGameLevel();
	gameOver = StateGameOver();

	state = STATE_GAME_LEVEL;
	
	currentState = &mainMenu;
	//currentState = &gameLevel;
	//currentState = &gameOver;
}

Application::~Application(){
	SDL_Quit();
}

void Application::Init(){
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RESOLUTION_X, RESOLUTION_Y, SDL_WINDOW_OPENGL);

	if (displayWindow){
		SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
		SDL_GL_MakeCurrent(displayWindow, context);
	}
	
	glViewport(0, 0, RESOLUTION_X, RESOLUTION_Y);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glClearColor(0.5f, 0.8f, 1.0f, 1.0f);


}

bool Application::Run(){
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS){
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	ProcessEvents();

	GAMESTATE nextState = currentState->getNextState();
	if (nextState != STATE_CURRENT){
		if (nextState == STATE_MAIN_MENU){
			currentState = &mainMenu;
			currentState->Init();

		}
		else if (nextState == STATE_GAME_LEVEL){
			currentState = &gameLevel;
			currentState->Init();
		}
		else if (nextState == STATE_GAME_OVER){
			currentState = &gameOver;
			currentState->Init();
		}
		else{

		}
	}

	while (fixedElapsed >= FIXED_TIMESTEP){
		fixedElapsed -= FIXED_TIMESTEP;
		Update(FIXED_TIMESTEP);
	}
	timeLeftOver = fixedElapsed;
	
	Render(elapsed);
	return done;
}

void Application::ProcessEvents(){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			done = true;
		}
		else{
			currentState->ProcessEvents(event);
		}
	}
}

void Application::Update(float elapsed){
	currentState->Update(elapsed);
}

void Application::Render(float elapsed){
	glClear(GL_COLOR_BUFFER_BIT);
	currentState->Render(elapsed);
	if (displayWindow){
		SDL_GL_SwapWindow(displayWindow);
	}
}

