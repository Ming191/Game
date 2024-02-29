#include "headers/game.h"

void game::init(const char* title) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to init SDL: " << SDL_GetError() << std::endl;
	} else {
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			std::cout << "Failed to create Window: " << SDL_GetError() << std::endl;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
			if(gRenderer == NULL) {
				std::cout << "Failed to create Renderer: " << SDL_GetError() << std::endl;
			}
		}
	}

	isRunning = true;
}

void game::handleEvent() {
	SDL_Event gEvent;

	while (isRunning)
	{
		while (SDL_PollEvent(&gEvent))
		{
			switch (gEvent.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;	
			
			default:
				break;
			}
		}
 	}
	
}

void game::render() {
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderPresent(gRenderer);
};

void game::update() {
	cnt++;
	std::cout << cnt << std::endl;	
};

void game::clean() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
};




