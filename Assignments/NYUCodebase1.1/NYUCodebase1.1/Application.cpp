#include "Application.h"

GAMESTATE state;




Application::Application(){
	Init();
	done = false;
	lastFrameTicks = 0.0f;
	mainMenu = StateMainMenu();

}

Application::~Application(){
	SDL_Quit();
}

void Application::Init(){
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	if (displayWindow){
		SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
		SDL_GL_MakeCurrent(displayWindow, context);
	}
	
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);


}

bool Application::Run(){
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	ProcessEvents();
	Update(elapsed);
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
		switch (state){
		case STATE_MAIN_MENU:
			mainMenu.ProcessEvents();         
			break;
		case STATE_GAME_LEVEL:
			//gameLevel.ProccessEvents();         
			break;
		}
	}
}

void Application::Update(float elapsed){
	switch (state){ 
		case STATE_MAIN_MENU:             
			mainMenu.Update(elapsed);         
			break;         
		case STATE_GAME_LEVEL:             
			//gameLevel.Update(elapsed);         
			break; 
	}

	//for (int i = 0; i < entities.size(); i++){
		//entities[i]->Update(elapsed);
	//}
}

void Application::Render(float elapsed){
	switch (state){
	case STATE_MAIN_MENU:
		mainMenu.Render(elapsed);         
		break;
	case STATE_GAME_LEVEL:
		//gameLevel.Render(elapsed);         
		break;
	}

	//DrawText1(texture, "hello world", 0.1, 0.00, 1.0, 1.0, 1.0, 1.0);
	//for (int i = 0; i < entities.size(); i++){
		//entities[i]->Render(elapsed);
	//}

	glClear(GL_COLOR_BUFFER_BIT);
	if (displayWindow){
		SDL_GL_SwapWindow(displayWindow);
	}

}

