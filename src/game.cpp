#include<headers/game.h>


game::game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;
	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	if (TTF_Init() < 0)
		std::cout << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;

	window.CreateWindow("Flappy Bird Updated by Ming");

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
	OK_Button = Button(Vector(SCREEN_WIDTH/6 - 20, 180.f), OK_ButtonTexture);

	startTexture = window.Load("res/gfx/StartButton.png");
	startButton  = Button(Vector(SCREEN_WIDTH/6 - 20, 148.f), startTexture);

	optionsTexture = window.Load("res/gfx/Options.png");
	optionsButton = Button(Vector(SCREEN_WIDTH/6 - 20, 170.f), optionsTexture);

	classicModeTexture = window.Load("res/gfx/ClassicMode.png");
	classicModeButton  = Button(Vector(SCREEN_WIDTH/6 - 20,148.f), classicModeTexture);

	hellModeTexture = window.Load("res/gfx/HellMode.png");
	hellModeButton  = Button(Vector(SCREEN_WIDTH/6 - 20,170.f), hellModeTexture);

	pauseTexture = window.Load("res/gfx/PauseButton.png");
	pauseButton  = Button(Vector(5.f,5.f), pauseTexture);
	
	playTexture = window.Load("res/gfx/PlayButton.png");
	playButton  = Button(Vector(5.f,5.f), playTexture);

	handTexture = window.Load("res/gfx/TutorialHand.png");
	getReadyTexture = window.Load("res/gfx/GetReadyText.png");
	BW_BirdTexture = window.Load("res/gfx/Bird4.png");
	tapTexture = window.Load("res/gfx/Tap.png");

	menuTexture = window.Load("res/gfx/MenuButton.png");
	menuButton  = Button(Vector(SCREEN_WIDTH/6 - 20,160.f), menuTexture);

	gameOverTexture = window.Load("res/gfx/GameOverText.png");
	scorePanelTexture = window.Load("res/gfx/ScorePanel.png");

	medalTexture[0] = window.Load("res/gfx/Bronze.png");
	medalTexture[1] = window.Load("res/gfx/Silver.png");
	medalTexture[2] = window.Load("res/gfx/Gold.png");

	CoinTextures[0] = window.Load("res/gfx/Coin1.png");
	CoinTextures[1] = window.Load("res/gfx/Coin2.png");
	CoinTextures[2] = window.Load("res/gfx/Coin3.png");
	CoinTextures[3] = window.Load("res/gfx/Coin4.png");
	CoinTextures[4] = window.Load("res/gfx/Coin5.png");

	for (int i = 0; i < 4; i++)
	{
	}
	
	flashTexture = window.Flash();


//  ---PipesTextureLoad---
	pipesTexture[0] = window.Load("res/gfx/PipeUp.png");
	pipesTexture[1] = window.Load("res/gfx/PipeDown.png");

	float pipeX = 240.f;
	for (int i = 1; i<=4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), pipesTexture[0], 1));
		// std::cout << pipeUpY + pipeUp[i].GetCurrFrame().h << std::endl;
		float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), pipesTexture[1], 0));
		// std::cout << pipeDownY << std::endl;
		Coins.emplace_back(Coin(Vector(pipeX + 13 - 8, pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP/2 - 8), CoinTextures[0]));
		pipeX += 90;
		// std::cout << "-----" << std::endl;
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
	std::string currScoreS = std::to_string(currScore);
	if(currScoreS.length() < 2) currScoreS = "0" + currScoreS;

	std::string highScoreS = std::to_string(highScore);
	if(highScoreS.length() < 2) highScoreS = "0" + highScoreS;

//  ---BackgroundRender---
	for (int i = 0; i<6; i++)
	{
		window.Render(bg[i]);
	}

	if (currGameState == PLAY || currGameState == PAUSE || currGameState == PENDING)
	{
		window.RenderText(Vector(13.f,230.f), currScoreS, "res/font/origa___.ttf", 80, white, 1);

	}
	
//  ---PipeRender---
	for (int i = 0; i<4; i++)
	{
		// window.Render(Coins[i]);
		window.Render(pipeUp[i]);
		window.Render(pipeDown[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		if(!(Coins[i].isHit && (hitTime[i] != 0 && SDL_GetTicks() - hitTime[i] > 300))) window.RenderRotate(CoinTextures[coinFrameIndex], Coins[i].GetPos(), 0);
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
		window.Render(titleTexture, Vector(SCREEN_WIDTH/6 - 96/2, 48.f));
		window.Render(startButton);
		window.Render(optionsButton);
		break;
	case MODE_SELECTION:
		window.Render(titleTexture, Vector(SCREEN_WIDTH/6 - 96/2, 48.f));
		window.Render(classicModeButton);
		window.Render(hellModeButton);
		break;
	case PENDING:
		window.Render(handTexture, Vector(SCREEN_WIDTH/6 - 6, 100.f));
		window.Render(getReadyTexture, Vector(SCREEN_WIDTH/6 - 87/2, 48.f));
		window.Render(BW_BirdTexture, Vector(SCREEN_WIDTH/6 - 19/2.f, 80.f));
		window.Render(tapTexture, Vector(SCREEN_WIDTH/6 - 11/2 + 25, 103.f));
	case PLAY:
		window.Render(pauseButton);
		break;
	case PAUSE:
		window.Render(playButton);
		break;
	case DIE:
		if (SDL_GetTicks() - deadTime > 800)
		{
			window.Render(OK_Button);
			window.Render(menuButton);
			window.Render(gameOverTexture, Vector(SCREEN_WIDTH/6 - 94/2, 48.f));
			window.Render(scorePanelTexture, Vector(SCREEN_WIDTH/6-113/2, 80.f));
			window.RenderText(Vector(290.f,280.f), currScoreS, "res/font/monogram-extended.ttf", 16 , white,0);
			window.RenderText(Vector(290.f,350.f), highScoreS, "res/font/monogram-extended.ttf", 16 , white,0);

			
			if (currScore > 10)
			{
				window.Render(medalTexture[0], Vector(29,101));
			} else if(currScore > 50)
			{
				window.Render(medalTexture[1], Vector(29,101));
			} else if(currScore > 100)
			{
				window.Render(medalTexture[2], Vector(29,101));
			}
		}
	default:
		break;
	}

//  ---BirdRender---
	window.RenderRotate(playerTexture[playerFrameIndex], p.GetPos(), p.GetAngle());

	if(currGameState == DIE)
	{
		if (flashAlpha > 0)
		{
			SDL_SetTextureAlphaMod(flashTexture, flashAlpha);
			window.Render(flashTexture, Vector(0,0));
			flashAlpha -= 5;
		}
	}
	
	
	window.Display();
}

void game::handleEvents()
{	
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
					switch (currGameState)
					{
					case PLAY:
						currGameState = PAUSE;
						break;
					case PAUSE:
						currGameState = PLAY;
						break;
					default:
						break;
					}
				} else if(event.key.keysym.sym == SDLK_SPACE)
				{
					switch (currGameState)
					{
					case PLAY:
						p.Fly();
						break;
					case PENDING:
						currGameState = PLAY;
						p.Fly();
						break;
					default:
						break;
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					switch (currGameState)
					{
					case MAIN_MENU:
						if (commonFunc::isCollide(mousePos, startButton))
						{
							currGameState = MODE_SELECTION;
						}
						break;
					case MODE_SELECTION:
						if(commonFunc::isCollide(mousePos, hellModeButton)) 
						{
							currGameState = PENDING;
							gameMode = HELL_MODE;
						}
						if(commonFunc::isCollide(mousePos, classicModeButton)) 
						{
							currGameState = PENDING;
							gameMode = CLASSIC_MODE;
						}
						break;
					case PENDING:
						currGameState = PLAY;
						p.Fly();
						break;
					case PLAY:
						p.Fly();
						break;
					case DIE:
						if(commonFunc::isCollide(mousePos, OK_Button)) GameReset();
						if(commonFunc::isCollide(mousePos, menuButton))
						{
							GameReset();
							currGameState = MAIN_MENU;
						};
						break;
					
					default:
						break;
					}		
				}
				break;
			}
		}
	}	
}

void game::Update()
{
	int m_x,m_y;
	SDL_GetMouseState(&m_x, &m_y);
	mousePos.SetX((float)m_x/3);
	mousePos.SetY((float)m_y/3);

	if(currGameState != DIE && currGameState != PAUSE)
	{
		if (_cTime >= _timeStep)
		{
			_cTime = 0.0f;
			playerFrameIndex += 1;
			coinFrameIndex += 1;
			if (playerFrameIndex > 2) playerFrameIndex = 0;
			if (coinFrameIndex > 4) coinFrameIndex = 0;
		}
		_cTime += 0.01f;
	}
		

	for (int i = 0; i < 4; i++)
	{
		if (pipeUp[i].isCrossed)
		{
			float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
			pipeUp[i].SetPos(Vector(pipeUp[i].GetPos().GetX(), pipeUpY));
			pipeUp[i].isCrossed = false;
			float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;

			pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(), pipeDownY));
			pipeDown[i].isCrossed = false;

			Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, pipeUpY + pipeUp[i].GetCurrFrame().h + PIPE_GAP/2 - 8));
			Coins[i].isHit = false;
			hitTime[i] = 0;
			// std::cout << pipeUpY + pipeUp[i].GetCurrFrame().h << std::endl;
			// std::cout << pipeDownY << std::endl;
			// std::cout << "-----" << std::endl;
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

		switch (gameMode)
		{
		case CLASSIC_MODE:
			for (int i = 0; i<4; i++)
			{
				{
					pipeUp[i].UpdateClassic();
					pipeDown[i].UpdateClassic();
				}
				pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(),pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h +PIPE_GAP));
				Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, Coins[i].GetPos().GetY()));
			}
			break;
		case HELL_MODE:
			for (int i = 0; i<4; i++)
			{
				{
					pipeUp[i].UpdateHell();
					pipeDown[i].UpdateHell();
				}
				pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(), pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h +PIPE_GAP));
				if(!Coins[i].isHit) Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h + PIPE_GAP/2 - 8));
				else Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, Coins[i].GetPos().GetY()));
			}
			break;
		default:
			break;
		}
		
		if(p.GetPos().GetY() < 0) p.SetPos(Vector(p.GetPos().GetX(), 0));

		for(int i = 0; i<2; i++)
		{
			if(commonFunc::isCollide(p,base[i])) currGameState = DIE;
		}

		if (scored)
		{
			scoreAccumulator += 0.02f;
			if (scoreAccumulator >= scoreStep)
			{
				scoreAccumulator = 0.f;
				scored = false;
			}
		}

		for (int i = 0; i<4; i++)
		{
			if (commonFunc::CheckPass(p, pipeDown[i].GetPos().GetX() + (pipeDown[i].GetCurrFrame().w / 2.f), pipeDown[i].GetPos().GetY()) && !scored)
			{
				scored = true;
				if (scored)
				{
					Coins[i].Update();
					if(hitTime[i] == 0) hitTime[i] = SDL_GetTicks();
					Coins[i].isHit = true;
				}
				
				currScore += 1;
			}
			if(commonFunc::isCollide(p, pipeUp[i]))    currGameState = DIE;
			if (commonFunc::isCollide(p, pipeDown[i])) currGameState = DIE;
		}
	}

	if(currGameState == DIE)
	{
		if(deadTime == 0) deadTime = SDL_GetTicks();
		p.Update();
		if(p.GetPos().GetY() > 190)
		{
			p.SetPos(Vector(p.GetPos().GetX(), 190));
		}
		
		std::ifstream inFile("res/HighScore.txt");
		if (inFile.is_open()) {
			inFile >> highScore;
			inFile.close();
		} else {
			std::cerr << "Unable to open file for reading high score. Assuming zero.\n";
		}

		if (currScore > highScore)
		{
			std::ofstream outFile("res/HighScore.txt");
			if (outFile.is_open()) {
				outFile << currScore;
				outFile.close();
			} else {
				std::cerr << "Unable to open file for writing high score.\n";
    		}
		}
		
	}

	
}

void game::GameReset()
{
	p.SetPos(Vector(30.f,100.f));
	p.SetAngle(0.f);
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
	Coins.clear();

	float pipeX = 240.f;
	for (int i = 0; i<4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), pipesTexture[0], 1));
		float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), pipesTexture[1], 0));
		Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h+PIPE_GAP/2 - 8));
		Coins[i].isHit = false;
		hitTime[i] = 0;
		// std::cout << pipeDownY << std::endl;
		pipeX += 90;
	}	
	currGameState = PENDING;
	currScore = 0;
	deadTime = 0;
	flashAlpha = 255;
}