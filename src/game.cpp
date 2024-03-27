#include<headers/game.h>

game::game()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;
	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	if (TTF_Init() == -1)
		std::cout << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;

	Window.CreateWindow("Flappy Bird");

//  ---PlayerTexture and Init---
	playerTexture[0] = Window.Load("res/gfx/Bird1.png");
	playerTexture[1] = Window.Load("res/gfx/Bird2.png");
	playerTexture[2] = Window.Load("res/gfx/Bird3.png");

	p = player(Vector(30,100), playerTexture[0]);
	
//  ---BackgroundTextureLoad---
	backgroundTexture[0] = Window.Load("res/gfx/background-day.png");
	backgroundTexture[1] = Window.Load("res/gfx/background-night.png");
	
	bg.emplace_back(background(Vector(0.f, 0.f), backgroundTexture[0]));
	bg.emplace_back(background(Vector(144.f, 0.f), backgroundTexture[0]));
	bg.emplace_back(background(Vector(288.f, 0.f), backgroundTexture[0]));
	bg.emplace_back(background(Vector(432.f, 0.f), backgroundTexture[1]));
	bg.emplace_back(background(Vector(576.f, 0.f), backgroundTexture[1]));
	bg.emplace_back(background(Vector(720.f, 0.f), backgroundTexture[1]));

//	---GroundTextureLoad----
	groundTexture = Window.Load("res/gfx/Ground1.png");
	base.emplace_back(ground(Vector(0.f, 200.f), groundTexture));
	base.emplace_back(ground(Vector(154.f, 200.f), groundTexture));

//	---GetScreenRefreshRate---
	std::cout << "Refresh Rate: " << Window.GetRefreshRate() << std::endl;
}

void game::clean()
{
	Window.Clean();
}

void game::render()
{
	Window.Clear();

//  ---BackgroundRender---
	for (int i = 0; i<6; i++)
	{
		if (!isBirdDead)
		{
			bg[i].update();
		}
		Window.Render(bg[i]);
	}

//  ---GroundRender---
	for (int i = 0; i < 2; i++)
	{
		if (!isBirdDead)
		{
			base[i].update();
		}
		Window.Render(base[i]);
	}
//  ---BirdRender---
	if(!isBirdDead)
	{
		if (_cTime >= _timeStep)
		{
			_cTime = 0.0f;
			index += 1;
			if (index > 2)
				index = 0;
		}
		_cTime += 0.005f;
	}
	Window.Render(playerTexture[index], p.getPos());

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
					quit = true;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if (!start)
						{
							start = !start;
						}
						
						p.fly();
					}
				}
			}
			std::cout << commonFunc::hireTimeInSec() << std::endl;
		}
		
	//}
}

void game::update()
{
	if (start)
	{
		p.update();
	}
	
}