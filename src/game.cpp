#include<headers/game.h>

bool game::initGraphic()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "SDL_image has Failed. Error: " << IMG_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;
	Window.CreateWindow("Flappy Bird");

	playerTexture = Window.Load("res/gfx/Bird1.png");

	player tmp(Vector(30,100), playerTexture);
	p = tmp;

	std::cout << "Refresh Rate: " << Window.GetRefreshRate() << std::endl;
	return 1;
}

void game::clean()
{
	Window.Clean();
}

void game::render()
{
	Window.Clear();
	if (!isBirdDead)
	{
		Window.Render(p);
	}
	Window.Display();
}

void game::run()
{	
	// while(1) 
	// {
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					isRunning = false;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						std::cout << "Clicked" << std::endl;
					}
				}
			}
			std::cout << commonFunc::hireTimeInSec() << std::endl;
			render();
		}
		
	//}
}

void game::update()
{

}