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

	window.CreateWindow("Flappy Bird");

//  ---PlayerTexture and Init---
	playerTexture[0] = window.Load("res/gfx/Bird1.png");
	playerTexture[1] = window.Load("res/gfx/Bird2.png");
	playerTexture[2] = window.Load("res/gfx/Bird3.png");

	p = Player(Vector(30,100), playerTexture[0]);
	
//  ---BackgroundTextureLoad---
	BackgroundTexture[0] = window.Load("res/gfx/Background-day.png");
	BackgroundTexture[1] = window.Load("res/gfx/Background-night.png");
	
	bg.emplace_back(Background(Vector(0.f,   0.f), BackgroundTexture[0]));
	bg.emplace_back(Background(Vector(144.f, 0.f), BackgroundTexture[0]));
	bg.emplace_back(Background(Vector(288.f, 0.f), BackgroundTexture[0]));
	bg.emplace_back(Background(Vector(432.f, 0.f), BackgroundTexture[1]));
	bg.emplace_back(Background(Vector(576.f, 0.f), BackgroundTexture[1]));
	bg.emplace_back(Background(Vector(720.f, 0.f), BackgroundTexture[1]));

//	---GroundTextureLoad---
	groundTexture = window.Load("res/gfx/Ground1.png");
	base.emplace_back(Ground(Vector(0.f, 200.f), groundTexture));
	base.emplace_back(Ground(Vector(154.f, 200.f), groundTexture));

//  ---ButtonTextureLoad---
	UI_OkButton = window.Load("res/gfx/OkButton.png");
	OK_button = button(Vector(47.f, 180.f), UI_OkButton);

//  ---PipesTextureLoad---
	pipesTexture[0] = window.Load("res/gfx/PipeUp.png");
	pipesTexture[1] = window.Load("res/gfx/PipeDown.png");

	// pipeUp.emplace_back(pipe(Vector(280.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));
	// pipeUp.emplace_back(pipe(Vector(350.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));
	// pipeUp.emplace_back(pipe(Vector(420.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));
	// pipeUp.emplace_back(pipe(Vector(490.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));

	// pipeDown.emplace_back(pipe(Vector(280.f,commonFunc::getRandomValues(PIPE_DOWN_MIN_Y, PIPE_DOWN_MAX_Y)), pipesTexture[1]));	
	// pipeDown.emplace_back(pipe(Vector(350.f,commonFunc::getRandomValues(PIPE_DOWN_MIN_Y, PIPE_DOWN_MAX_Y)), pipesTexture[1]));
	// pipeDown.emplace_back(pipe(Vector(420.f,commonFunc::getRandomValues(PIPE_DOWN_MIN_Y, PIPE_DOWN_MAX_Y)), pipesTexture[1]));
	// pipeDown.emplace_back(pipe(Vector(490.f,commonFunc::getRandomValues(PIPE_DOWN_MIN_Y, PIPE_DOWN_MAX_Y)), pipesTexture[1]));
	float pipeX = 240.f;
	for (int i = 1; i<=4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), pipesTexture[0], 1));
		float pipeDownY = pipeUpY + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), pipesTexture[1], 0));
		std::cout << pipeDownY << std::endl;
		pipeX += 90;
	}	

//	---GetScreenRefreshRate---
	std::cout << "Refresh Rate: " << window.GetRefreshRate() << std::endl;
}

void game::Clean()
{
	window.Clean();
}

void game::Render()
{
	window.Clear();

		
//  ---BackgroundRender---
	for (int i = 0; i<6; i++)
	{
		if (gameState != DIE)
		{
			bg[i].Update();
		}
		window.Render(bg[i]);
	}

//  ---PipeRender---
	for (int i = 0; i<4; i++)
	{
		if (gameState != DIE && gameState == PLAY)
		{
			pipeUp[i].Update();
			pipeDown[i].Update();
			pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(),pipeUp[i].GetPos().GetY()+PIPE_GAP));
		}
		window.Render(pipeUp[i]);
		window.Render(pipeDown[i]);
	}


//  ---GroundRender---
	for (int i = 0; i < 2; i++)
	{
		if (gameState != DIE)
		{
			base[i].Update();
		}
		window.Render(base[i]);
	}

//  ---BirdRender---
	if(gameState != DIE)
	{
		if (_cTime >= _timeStep)
		{
			_cTime = 0.0f;
			index += 1;
			if (index > 2)
				index = 0;
		}
		_cTime += 0.01f;
	}
	window.Render(playerTexture[index], p.GetPos());

	if(gameState == DIE)
	{
		window.Render(OK_button);
	}

	window.Display();
}

void game::Run()
{	
	// while(1) 
	// {
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					gameState = QUIT;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						// std::cout << mousePos.GetX() << " " << mousePos.GetY() << std::endl;
						if (gameState == PENDING)
						{
							gameState = PLAY;
						}
						
						if(gameState != DIE)
						{
							p.Fly();
						}
						
						if(gameState == DIE && commonFunc::isCollide(mousePos, OK_button))
						{
							GameReset();
						}
					}
				}
				// case SDL_MOUSEMOTION:
				// 	std::cout << event.motion.x << " " << event.motion.y << std::endl;
			}
			// std::cout << commonFunc::hireTimeInSec() << std::endl;
		}
		
	//}
}

void game::Update()
{
	int m_x,m_y;
	SDL_GetMouseState(&m_x, &m_y);
	mousePos.SetX((float)m_x/3);
	mousePos.SetY((float)m_y/3);

	srand((unsigned int)time(0));
	for (int i = 0; i < 4; i++)
	{
		if (pipeUp[i].isCrossed)
		{
			float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
			pipeUp[i].SetPos(Vector(pipeUp[i].GetPos().GetX(), pipeUpY));
			pipeUp[i].isCrossed = false;
			float pipeDownY = pipeUpY + PIPE_GAP;
			std::cout << pipeDownY << std::endl;

			pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(), pipeDownY));
			pipeDown[i].isCrossed = false;
		}
	}

	if (gameState == PLAY)
	{
		p.Update();
		
		if(gameState != DIE)
		{
			if(p.GetPos().GetY() < 0) gameState = DIE;
			for(int i = 0; i<2; i++)
			{
				if(commonFunc::isCollide(p,base[i])) gameState = DIE;
			}
			for (int i = 0; i<4; i++)
			{
				if(commonFunc::isCollide(p, pipeUp[i]))   gameState = DIE;
				if (commonFunc::isCollide(p,pipeDown[i])) gameState = DIE;
			}
		}
	}
	
}

void game::GameReset()
{
	p.SetPos(Vector(30.f,100.f));
	bg.clear();
	bg.emplace_back(Background(Vector(0.f,   0.f), BackgroundTexture[0]));
	bg.emplace_back(Background(Vector(144.f, 0.f), BackgroundTexture[0]));
	bg.emplace_back(Background(Vector(288.f, 0.f), BackgroundTexture[0]));
	bg.emplace_back(Background(Vector(432.f, 0.f), BackgroundTexture[1]));
	bg.emplace_back(Background(Vector(576.f, 0.f), BackgroundTexture[1]));
	bg.emplace_back(Background(Vector(720.f, 0.f), BackgroundTexture[1]));

	pipeUp.clear();
	pipeDown.clear();

	float pipeX = 240.f;
	for (int i = 1; i<=4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), pipesTexture[0], 1));
		float pipeDownY = pipeUpY + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), pipesTexture[1], 0));
		std::cout << pipeDownY << std::endl;
		pipeX += 90;
	}	
	gameState = PENDING;
}