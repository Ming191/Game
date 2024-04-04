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

//  ---MiscTexture---

	titleTexture = window.Load("res/gfx/FlappyBirdText.png");

//  ---PlayerTexture and Init---
	playerTexture[0] = window.Load("res/gfx/Bird1.png");
	playerTexture[1] = window.Load("res/gfx/Bird2.png");
	playerTexture[2] = window.Load("res/gfx/Bird3.png");

	p = Player(Vector(30,100), playerTexture[0]);
	
//  ---BackgroundTextureLoad---
	BackgroundTexture[0] = window.Load("res/gfx/Background-day.png");
	BackgroundTexture[1] = window.Load("res/gfx/Background-night.png");

	float bgX = 0;
	for (int i=0; i<3; i++)
	{
		bg.emplace_back(Background(Vector(bgX, 0.f), BackgroundTexture[0]));
		bgX +=144.f;
	}
	for (int i=0; i<3; i++)
	{
		bg.emplace_back(Background(Vector(bgX, 0.f), BackgroundTexture[1]));
		bgX +=144.f;
	}

//	---GroundTextureLoad---
	groundTexture = window.Load("res/gfx/Ground1.png");
	base.emplace_back(Ground(Vector(0.f, 200.f), groundTexture));
	base.emplace_back(Ground(Vector(154.f, 200.f), groundTexture));

//  ---ButtonTextureLoad---
	OK_ButtonTexture = window.Load("res/gfx/OkButton.png");
	OK_Button = Button(Vector(48.f, 180.f), OK_ButtonTexture);

	startTexture = window.Load("res/gfx/StartButton.png");
	startButton  = Button(Vector(48.f, 148.f), startTexture);

	optionsTexture = window.Load("res/gfx/Options.png");
	optionsButton = Button(Vector(48.f, 170.f), optionsTexture);

	classicModeTexture = window.Load("res/gfx/ClassicMode.png");
	classicModeButton  = Button(Vector(48.f,148.f), classicModeTexture);

	hellModeTexture = window.Load("res/gfx/HellMode.png");
	hellModeButton  = Button(Vector(48.f,170.f), hellModeTexture);

	pauseTexture = window.Load("res/gfx/PauseButton.png");
	pauseButton  = Button(Vector(5.f,5.f), pauseTexture);
	
	playTexture = window.Load("res/gfx/PlayButton.png");
	playButton  = Button(Vector(5.f,5.f), playTexture);


//  ---PipesTextureLoad---
	pipesTexture[0] = window.Load("res/gfx/PipeUp.png");
	pipesTexture[1] = window.Load("res/gfx/PipeDown.png");

	// pipeUp.emplace_back(pipe(Vector(280.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));
	// pipeUp.emplace_back(pipe(Vector(348.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));
	// pipeUp.emplace_back(pipe(Vector(420.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));
	// pipeUp.emplace_back(pipe(Vector(490.f,commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y)), pipesTexture[0]));

	// pipeDown.emplace_back(pipe(Vector(280.f,commonFunc::getRandomValues(PIPE_DOWN_MIN_Y, PIPE_DOWN_MAX_Y)), pipesTexture[1]));	
	// pipeDown.emplace_back(pipe(Vector(348.f,commonFunc::getRandomValues(PIPE_DOWN_MIN_Y, PIPE_DOWN_MAX_Y)), pipesTexture[1]));
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
		window.Render(bg[i]);
	}

//  ---PipeRender---
	for (int i = 0; i<4; i++)
	{
		window.Render(pipeUp[i]);
		window.Render(pipeDown[i]);
	}


//  ---GroundRender---
	for (int i = 0; i < 2; i++)
	{
		window.Render(base[i]);
	}
//  ---UI Render---

	switch (currGameState)
	{
	case MAIN_MENU:
		window.Render(titleTexture, Vector(25.f, 48.f));
		window.Render(startButton);
		window.Render(optionsButton);
		break;
	case MODE_SELECTION:
		window.Render(titleTexture, Vector(25.f, 48.f));
		window.Render(classicModeButton);
		window.Render(hellModeButton);
		break;
	case PLAY:
		window.Render(pauseButton);
		break;
	case PAUSE:
		window.Render(playButton);
		break;
	default:
		break;
	}

//  ---BirdRender---
	if(currGameState != DIE && currGameState != PAUSE)
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

	if(currGameState == DIE)
	{
		window.Render(OK_Button);
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
					currGameState = QUIT;
					break;
				}

				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						if(currGameState == PLAY)
						{
							currGameState = PAUSE;
						}
						else if(currGameState == PAUSE)
						{
							currGameState  = PLAY;
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						std::cout << mousePos.GetX() << " " << mousePos.GetY() << std::endl;

						switch (currGameState)
						{
						case MAIN_MENU:
							if (commonFunc::isCollide(mousePos, startButton))
							{
								currGameState = MODE_SELECTION;
							}
							break;
						case MODE_SELECTION:
							if(commonFunc::isCollide(mousePos, hellModeButton)) currGameState = PENDING;
							break;
						
						default:
							break;
						}		
						if (currGameState == PENDING)
						{
							currGameState = PLAY;
						}
						
						if(currGameState != DIE)
						{
							p.Fly();
						}
						
						if(currGameState == DIE && commonFunc::isCollide(mousePos, OK_Button))
						{
							GameReset();
						}
					}
					break;
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
			// std::cout << pipeDownY << std::endl;

			pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(), pipeDownY));
			pipeDown[i].isCrossed = false;
		}
	}

	if(currGameState != DIE && currGameState != PAUSE)
	{
		for (int i = 0; i < 2; i++)
		{
			base[i].Update();
		}
	}

	if (currGameState == PLAY)
	{
		p.Update();
		for (int i = 0; i<6; i++)
		{
			bg[i].Update();
		}
		for (int i = 0; i<4; i++)
		{
			pipeUp[i].Update();
			pipeDown[i].Update();
			pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(),pipeUp[i].GetPos().GetY()+PIPE_GAP));

		}
		if(p.GetPos().GetY() < 0) currGameState = DIE;
		for(int i = 0; i<2; i++)
		{
			if(commonFunc::isCollide(p,base[i])) currGameState = DIE;
		}
		for (int i = 0; i<4; i++)
		{
			if(commonFunc::isCollide(p, pipeUp[i]))    currGameState = DIE;
			if (commonFunc::isCollide(p, pipeDown[i])) currGameState = DIE;
		}
	}
	
}

void game::GameReset()
{
	p.SetPos(Vector(30.f,100.f));

	bg.clear();
	float bgX = 0;
	for (int i=0; i<3; i++)
	{
		bg.emplace_back(Background(Vector(bgX, 0.f), BackgroundTexture[0]));
		bgX +=144.f;
	}
	for (int i=0; i<3; i++)
	{
		bg.emplace_back(Background(Vector(bgX, 0.f), BackgroundTexture[1]));
		bgX +=144.f;
	}

	pipeUp.clear();
	pipeDown.clear();

	float pipeX = 240.f;
	for (int i = 1; i<=4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), pipesTexture[0], 1));
		float pipeDownY = pipeUpY + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), pipesTexture[1], 0));
		// std::cout << pipeDownY << std::endl;
		pipeX += 90;
	}	
	currGameState = PENDING;
}