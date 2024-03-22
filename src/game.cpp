#include<headers/game.h>

game::game() {


}

bool game::initGraphic()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "SDL_image has Failed. Error: " << IMG_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;
	Window.CreateWindow("Flappy Bird");

	std::cout << "Refresh Rate: " << Window.GetRefreshRate() << std::endl;
	return 1;
}

void game::clean()
{
	Window.Clean();
}

void game::render()
{

}

void game::handleEvents()
{	
	while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					isRunning = false;
					break;
				}
			}
			
		}
}

void game::update()
{

}