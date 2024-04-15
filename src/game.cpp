#include<headers/game.h>


game::game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;
	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	if (TTF_Init() < 0)
		std::cout << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;
	window.CreateWindow("ChimChim");

//  ---MiscTexture---
	titleTexture = window.Load("res/gfx/FlappyBirdText.png");
	gameOverTexture = window.Load("res/gfx/GameOverText.png");
	scorePanelTexture = window.Load("res/gfx/ScorePanel.png");

//  ---PlayerTexture and Init---
	playerTexture[0] = window.Load("res/gfx/Girl1.png");
	playerTexture[1] = window.Load("res/gfx/Girl2.png");
	playerTexture[2] = window.Load("res/gfx/Girl3.png");
	playerTexture[3] = window.Load("res/gfx/Girl4.png");

	p = Player(Vector(30,120), playerTexture[0], SFX);
//	---GroundTextureLoad---
	groundTexture = window.Load("res/gfx/Ground2.png");
	base.emplace_back(Ground(Vector(0.f, 200.f), groundTexture));
	base.emplace_back(Ground(Vector(154.f, 200.f), groundTexture));

//  ---ButtonTextureLoad---
	OK_ButtonTexture = window.Load("res/gfx/OkButton.png");
	OK_Button = Button(Vector(SCREEN_WIDTH/6 - 20, 180.f), OK_ButtonTexture);

	shopTexture = window.Load("res/gfx/Shop.png");
	shopButton = Button(Vector(SCREEN_WIDTH/3 - 5 - 16,SCREEN_HEIGHT/3 - 5 - 40), shopTexture);

	startTexture = window.Load("res/gfx/StartButton.png");
	startButton  = Button(Vector(SCREEN_WIDTH/6 - 20, 148.f), startTexture);

	classicModeTexture = window.Load("res/gfx/ClassicMode.png");
	classicModeButton  = Button(Vector(SCREEN_WIDTH/6 - 20,148.f), classicModeTexture);

	hellModeTexture = window.Load("res/gfx/HellMode.png");
	hellModeButton  = Button(Vector(SCREEN_WIDTH/6 - 20,170.f), hellModeTexture);

	pauseTexture = window.Load("res/gfx/PauseButton.png");
	pauseButton  = Button(Vector(5.f,5.f), pauseTexture);
	
	playTexture = window.Load("res/gfx/PlayButton.png");
	playButton  = Button(Vector(5.f,5.f), playTexture);

	BW_BirdTexture = window.Load("res/gfx/Bird4.png");

	menuTexture = window.Load("res/gfx/MenuButton.png");
	menuButton  = Button(Vector(SCREEN_WIDTH/6 - 20,160.f), menuTexture);

	musicPlayerPanelTexture = window.Load("res/gfx/musicPlayerPanel.png");
	musicPlayerTexture = window.Load("res/gfx/musicPlayer.png");
	musicPlayerButton  = Button(Vector(SCREEN_WIDTH/3 - 5 - 16 ,SCREEN_HEIGHT/3 - 5- 16), musicPlayerTexture);
	musicPlayerPlayTexture = window.Load("res/gfx/Sound.png");
	musicPlayerMuteTexture = window.Load("res/gfx/SoundMute.png");
	musicPlayerPlayButton = Button(Vector(18,130), musicPlayerPlayTexture);
	sfxPlayerButton = Button(Vector(18,150), musicPlayerPlayTexture);

	forwardTexture = window.Load("res/gfx/forward.png");
	backwardTexture = window.Load("res/gfx/backward.png");
	forwardButton = Button(Vector(110,130), forwardTexture);
	backwardButton = Button(Vector(80, 130), backwardTexture);

	handleButton = Button(Vector((130-30)/2+30-6,165), window.Load("res/gfx/handle.png"));
	bar = Button(Vector(30, 168), window.Load("res/gfx/bar.png"));

	medalTexture[0] = window.Load("res/gfx/Bronze.png");
	medalTexture[1] = window.Load("res/gfx/Silver.png");
	medalTexture[2] = window.Load("res/gfx/Gold.png");

	CoinTextures[0] = window.Load("res/gfx/Coin1.png");
	CoinTextures[1] = window.Load("res/gfx/Coin2.png");
	CoinTextures[2] = window.Load("res/gfx/Coin3.png");
	CoinTextures[3] = window.Load("res/gfx/Coin4.png");
	CoinTextures[4] = window.Load("res/gfx/Coin5.png");

	spaceTexture[0] = window.Load("res/gfx/Space1.png");
	spaceTexture[1] = window.Load("res/gfx/Space2.png");
	SpaceIMG = Entity(Vector(SCREEN_WIDTH/6 - 32,160), spaceTexture[0]);
	thanksIMG = window.Load("res/gfx/Thanks.png");
	
	flashTexture = window.Flash();

//  ---PipesTextureLoad---
	pipesTexture[0] = window.Load("res/gfx/PipeUpSilver.png");
	pipesTexture[1] = window.Load("res/gfx/PipeDownSilver.png");

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
	musicPlayer.PlayCurrentTrack();
	pBG = ParallaxBG(window, currScore);
	SDL_Texture* foreGroundTexture = window.Load("res/gfx/clouds_mg_1_lightened.png");
	SDL_SetTextureAlphaMod(foreGroundTexture,180);
	foreGround.emplace_back(Background(Vector(0,-22), foreGroundTexture, 0.5f));
	foreGround.emplace_back(foreGround[0]);
	foreGround[1].SetPos(Vector(foreGround[0].GetCurrFrame().w,foreGround[0].GetPos().GetY()));
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

	pBG.Render();
	for (int i = 0; i < 4; i++)
	{
		if(!(Coins[i].isHit && (hitTime[i] != 0 && SDL_GetTicks() - hitTime[i] > 600))) window.Render(Coins[i]);
	}
//  ---PipeRender---
	for (int i = 0; i<4; i++)
	{
		// window.Render(Coins[i]);
		window.Render(pipeUp[i]);
		window.Render(pipeDown[i]);
	}
	
//  ---GroundRender---
	for (int i = 0; i < 2; i++)
	{
		window.Render(base[i]);
	}

	for (int i = 0; i < foreGround.size(); i++)
	{
		window.RenderScale(foreGround[i],4);
	}
//  ---UI Render---
	switch (currGameState)
	{
	case MAIN_MENU:
		window.Render(titleTexture, Vector(SCREEN_WIDTH/6 - 96/2, 20.f));
		window.Render(musicPlayerButton);
		window.Render(shopButton);
		window.Render(startButton);
		window.RenderScale(thanksIMG, Vector(0.f,300.f), 2);

		break;
	case MODE_SELECTION:
		window.Render(titleTexture, Vector(SCREEN_WIDTH/6 - 96/2, 20.f));
		window.Render(classicModeButton);
		window.Render(hellModeButton);
		break;
	case PENDING:
		window.Render(BW_BirdTexture, Vector(SCREEN_WIDTH/6 - 19/2.f, 80.f));
		window.Render(SpaceIMG);
		break;
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
			window.RenderScale(gameOverTexture, Vector(SCREEN_WIDTH/6 - 192/4 - 10, 48.f), 2);
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
		break;
	case MUSIC_MANAGER:
		window.Render(musicPlayerPanelTexture,Vector(0, 80));
		window.RenderText(Vector(56,320), musicPlayer.GetTitle(),"res/font/monogram-extended.ttf", 16, white, 0);
		window.Render(musicPlayerPlayButton);
	    window.RenderText(Vector(115,390), "Music" ,"res/font/monogram-extended.ttf", 16, white, 0);
	    window.RenderText(Vector(115,450), "SFX" ,"res/font/monogram-extended.ttf", 16, white, 0);
		window.Render(sfxPlayerButton);
		window.Render(backwardButton);
		window.Render(forwardButton);
		window.Render(bar);
		window.Render(handleButton);
		break;
	default:
		break;
	}

//  ---BirdRender---
	if(currGameState != MUSIC_MANAGER)
	window.RenderRotate(p, p.GetPos(), 0);

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

void game::HandleEvents()
{	
	while (SDL_PollEvent(&event))
	{
		if (currGameState == MUSIC_MANAGER)
		{
			if ((event.type == SDL_MOUSEMOTION )&& (event.motion.state & SDL_BUTTON_LMASK))
			{
				if ((commonFunc::isCollide(mousePos,handleButton) || commonFunc::isCollide(mousePos, bar)) && (mousePos.GetX()>=30 && mousePos.GetX() <= 130))
				{
				handleButton.SetPos(Vector(mousePos.GetX()-6,handleButton.GetPos().GetY()));
				masterVolume = (handleButton.GetPos().GetX()-30) / 100.f;
				musicPlayer.SetVolume(masterVolume);
				SFX.SetVolume(masterVolume);
				}
			}
			
		}
		
		switch (event.type)
		{
			case SDL_QUIT:
				currGameState = QUIT;
				break;
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
					case MUSIC_MANAGER:
						currGameState = MAIN_MENU;
						break;
					default:
						break;
					}
				} 
				else if(event.key.keysym.sym == SDLK_SPACE)
				{
					switch (currGameState)
					{
					case PLAY:
						p.Fly();
						break;
					case PENDING:
						currGameState = PLAY;
						p.Fly();
						pBG.SwitchState();
						break;
					default:
						break;
					}
				} else if(event.key.keysym.sym == SDLK_RIGHT)
				{
					musicPlayer.NextTrack();
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
						if (commonFunc::isCollide(mousePos, musicPlayerButton))
						{
							currGameState = MUSIC_MANAGER;
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
						pBG.SwitchState();
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
					case MUSIC_MANAGER:
						if(commonFunc::isCollide(mousePos, musicPlayerPlayButton))
						{
							if (musicPlayer.IsPlaying())
							{
								musicPlayerPlayButton.SetTex(musicPlayerMuteTexture);
								musicPlayer.Mute();
							}
							else
							{
								musicPlayerPlayButton.SetTex(musicPlayerPlayTexture);
								musicPlayer.UnMute();
							}
						}
						if (commonFunc::isCollide(mousePos, sfxPlayerButton))
						{
							if(!SFX.IsMuted())
							{
								sfxPlayerButton.SetTex(musicPlayerMuteTexture);
								for (int i = 0; i < TOTAL_CHUNK; i++)
								{
									SFX.Mute(i);
								}
								SFX.SwitchState();
							}
							else
							{
								sfxPlayerButton.SetTex(musicPlayerPlayTexture);
								for (int i = 0; i < TOTAL_CHUNK; i++)
								{
									SFX.UnMute(i);
								}
								SFX.SwitchState();
							}
						}

						if (commonFunc::isCollide(mousePos, bar))
						{
							handleButton.SetPos(Vector(mousePos.GetX()-6,handleButton.GetPos().GetY()));
							masterVolume = (handleButton.GetPos().GetX()-30) / 100.f;
							musicPlayer.SetVolume(masterVolume);
							SFX.SetVolume(masterVolume);	
						}
						if (commonFunc::isCollide(mousePos, backwardButton))
						{
							musicPlayer.PreviousTrack();
						}
						if (commonFunc::isCollide(mousePos, forwardButton))
						{
							musicPlayer.NextTrack();
						}
						
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
			spaceFrameIndex += 1;
			if (playerFrameIndex > 3) playerFrameIndex = 0;
			if (coinFrameIndex > 4) coinFrameIndex = 0;
			if(spaceFrameIndex > 1) spaceFrameIndex = 0;
		}
		_cTime += 0.01f;
	}
	p.SetTex(playerTexture[playerFrameIndex]);
	SpaceIMG.SetTex(spaceTexture[spaceFrameIndex]);

	for (int i = 0; i < 4; i++)
	{
		Coins[i].SetTex(CoinTextures[coinFrameIndex]);
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

	if (currGameState != DIE && currGameState != PLAY && currGameState != PAUSE)
	{
		p.Pending(0.8f);
	}

	if(currGameState != DIE && currGameState != PAUSE)
	{
		for (int i = 0; i < 2; i++)
		{
			base[i].Update();
		}
		for (int i = 0; i < foreGround.size(); i++)
		{
			foreGround[i].Update();
		}
		pBG.Update();
	}

	if (currGameState == PLAY)
	{
		p.Update();
		
		
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
			if(commonFunc::isCollide(p,base[i])) 
			{
				currGameState = DIE;
				SFX.Play(PIPE_HIT);
			};
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
					if(hitTime[i] == 0) hitTime[i] = SDL_GetTicks();
					Coins[i].isHit = true;
				}
				
				currScore += 1;
			}
			if(Coins[i].isHit)
			{
				if(SDL_GetTicks() - hitTime[i] < 20)
				{
					SFX.Play(COIN_HIT);
				}
				Coins[i].Update();
			}
			if(commonFunc::isCollide(p, pipeUp[i]) || commonFunc::isCollide(p, pipeDown[i]))
			{
				SFX.Play(PIPE_HIT);
				currGameState = DIE;
			};
;
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
	pBG.SwitchState();

	pipeUp.clear();
	pipeDown.clear();
	Coins.clear();
	pBG.Reset();
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