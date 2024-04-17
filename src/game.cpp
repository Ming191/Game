#include<headers/game.h>

game::game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	std::cerr << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;
	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	if (TTF_Init() < 0)
		std::cerr << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;
	window.CreateWindow("Fluffy Cat");
	TManager = TextureManager(window);
	TManager.LoadTexture();

	BManager = ButtonManager(TManager);
	BManager.LoadButton();
	p = Player(Vector(SCREEN_WIDTH/6-10,100), window.Load("res/gfx/Player/Cat/kitty1.png") , SFX, TManager);
	
//	---GroundTextureLoad---
	base.emplace_back(Ground(Vector(0.f, 200.f), TManager.groundTexture));
	base.emplace_back(Ground(Vector(154.f, 200.f), TManager.groundTexture));

	float pipeX = 240.f;
	for (int i = 1; i<=4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), TManager.pipesTexture[0], 1));
		float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), TManager.pipesTexture[1], 0));
		Coins.emplace_back(Coin(Vector(pipeX + 13 - 8, pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP/2 - 8), TManager.CoinTextures[0]));
		pipeX += 90;
	}

//	---AudioInit---
	musicPlayer.SetVolume(0.5f);
	SFX.SetVolume(0.1f);
	musicPlayer.PlayCurrentTrack();


//	---BackgroundAndForeGroundInit---
	pBG = ParallaxBG(window, currScore);
	SDL_Texture* foreGroundTexture = window.Load("res/gfx/clouds_mg_1_lightened.png");
	SDL_SetTextureAlphaMod(foreGroundTexture,180);
	foreGround.emplace_back(Background(Vector(0,-22), foreGroundTexture, 0.5f));
	foreGround.emplace_back(foreGround[0]);
	foreGround[1].SetPos(Vector(foreGround[0].GetCurrFrame().w,foreGround[0].GetPos().GetY()));

//	---Shop---
	std::ifstream inFileCoin("res/Coin.txt");
	if (inFileCoin.is_open()) {
		inFileCoin >> totalCoin;
		inFileCoin.close();
	} else {
		std::cerr << "Unable to open file for coins.\n";
	}
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

//  ---UI Render---
	switch (currGameState)
	{
	case MAIN_MENU:
		window.RenderScale(TManager.titleTexture, Vector(SCREEN_WIDTH/8 - 110/2, 20.f), 4);
		window.Render(BManager.startButton);
		window.Render(TManager.totalCoinTexture, Vector(SCREEN_WIDTH/3 -5 - 40, 5));
		window.RenderText(Vector(330, 16), std::to_string(totalCoin), "res/font/monogram-extended.ttf", 16, white, 0);
		break;
	case MODE_SELECTION:
		window.RenderScale(TManager.titleTexture, Vector(SCREEN_WIDTH/8 - 110/2, 20.f), 4);
		window.Render(BManager.classicModeButton);
		window.Render(BManager.hellModeButton);
		break;
	case PENDING:
		window.Render(BManager.SpaceIMG);
		break;
	case PLAY:
		window.Render(BManager.pauseButton);
		break;
	case PAUSE:
		window.Render(BManager.playButton);
		break;
	case DIE:
		if (SDL_GetTicks() - deadTime > 800)
		{
			window.Render(BManager.OK_Button);
			window.Render(BManager.menuButton);
			window.RenderScale(TManager.gameOverTexture, Vector(SCREEN_WIDTH/6 - 192/4 - 10, 48.f), 2);
			window.Render(TManager.scorePanelTexture, Vector(SCREEN_WIDTH/6-113/2, 80.f));
			window.RenderText(Vector(290.f,280.f), currScoreS, "res/font/monogram-extended.ttf", 16 , white,0);
			window.RenderText(Vector(290.f,350.f), highScoreS, "res/font/monogram-extended.ttf", 16 , white,0);

			if (currScore > 10)
			{
				window.Render(TManager.medalTexture[0], Vector(29,101));
			} else if(currScore > 50)
			{
				window.Render(TManager.medalTexture[1], Vector(29,101));
			} else if(currScore > 100)
			{
				window.Render(TManager.medalTexture[2], Vector(29,101));
			}
		}
		break;
	case MUSIC_MANAGER:
		window.Render(TManager.musicPlayerPanelTexture,Vector(0, 80));
		window.RenderText(Vector(56,320), musicPlayer.GetTitle(),"res/font/monogram-extended.ttf", 16, white, 0);
		window.Render(BManager.musicPlayerPlayButton);
	    window.RenderText(Vector(115,390), "Music" ,"res/font/monogram-extended.ttf", 16, white, 0);
	    window.RenderText(Vector(115,450), "SFX" ,"res/font/monogram-extended.ttf", 16, white, 0);
		window.Render(BManager.sfxPlayerButton);
		window.Render(BManager.PauseAndResumeMusic);
		window.Render(BManager.backwardButton);
		window.Render(BManager.forwardButton);
		window.Render(BManager.bar1);
		window.Render(BManager.bar2);
		window.Render(BManager.handleButton1);
		window.Render(BManager.handleButton2);
		break;
	case SHOP:
		window.RenderScale(TManager.shopPanel, Vector(SCREEN_WIDTH/12-24, SCREEN_HEIGHT/12-24),6);
		window.Render(BManager.previousChar);
		window.Render(BManager.nextChar);
		window.Render(BManager.selectButton);
		window.Render(TManager.totalCoinTexture, Vector(SCREEN_WIDTH/3 -5 - 40, 5));
		window.RenderText(Vector(330, 16), std::to_string(totalCoin), "res/font/monogram-extended.ttf", 16, white, 0);
		if (price[characterIndex] > 0)
		{
			window.RenderText(Vector(190,538), std::to_string(price[characterIndex]), "res/font/monogram-extended.ttf", 16, white, 0);
		}
		

	default:
		break;
	}

//  ---BirdRender---
	if(currGameState != MUSIC_MANAGER)
	window.RenderRotate(p, p.GetPos(), 0);

	for (int i = 0; i < foreGround.size(); i++)
	{
		window.RenderScale(foreGround[i],4);
	}

	if(currGameState == DIE)
	{
		if (flashAlpha > 0)
		{
			SDL_SetTextureAlphaMod(TManager.flashTexture, flashAlpha);
			window.Render(TManager.flashTexture, Vector(0,0));
			flashAlpha -= 5;
		}
	}
		
	if(currGameState == MAIN_MENU)
	{
		window.Render(BManager.musicPlayerButton);
		window.Render(BManager.shopButton);
		window.RenderScale(TManager.thanksIMG, Vector(0.f,300.f), 2);
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
				if ((commonFunc::isCollide(mousePos,BManager.handleButton1) || commonFunc::isCollide(mousePos, BManager.bar1)) && (mousePos.GetX()>=30 && mousePos.GetX() <= 130))
				{
				BManager.handleButton1.SetPos(Vector(mousePos.GetX()-6, BManager.handleButton1.GetPos().GetY()));
				musicVolume = (BManager.handleButton1.GetPos().GetX()-30) / 100.f;
				musicPlayer.SetVolume(musicVolume);
				}
				if ((commonFunc::isCollide(mousePos,BManager.handleButton2) || commonFunc::isCollide(mousePos, BManager.bar2)) && (mousePos.GetX()>=30 && mousePos.GetX() <= 130))
				{
				BManager.handleButton2.SetPos(Vector(mousePos.GetX()-6, BManager.handleButton2.GetPos().GetY()));
				sfxVolume = (BManager.handleButton2.GetPos().GetX()-30) / 100.f;
				SFX.SetVolume(sfxVolume);
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
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					switch (currGameState)
					{
					case MAIN_MENU:
						if (commonFunc::isCollide(mousePos, BManager.startButton))
						{
							currGameState = MODE_SELECTION;
						}
						if (commonFunc::isCollide(mousePos, BManager.musicPlayerButton))
						{
							currGameState = MUSIC_MANAGER;
						}
						if (commonFunc::isCollide(mousePos, BManager.shopButton))
						{
							std::ifstream inFilePrice("res/Price.txt");
							if (inFilePrice.is_open())
							{
								int n;
								int i = 0;
								while (inFilePrice >> n)
								{
									price[i++] = n;
								}
								inFilePrice.close();
							}  else {
								std::cerr << "Unable to open file for price.\n";
							}
							currGameState = SHOP;
							p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, SCREEN_HEIGHT/6 - p.GetCurrFrame().h/2));
						}
						break;
					// case SHOP:
						// if (commonFunc::isCollide(mousePos, nextChar) || commonFunc::isCollide(mousePos, previousChar))
						// {
						// 	for (int i = 0; i < price.size(); i++)
						// 	{
						// 		std::cout << price[i] << " ";
						// 	}
						// 	std::cout << std::endl;
							

						// 	if (commonFunc::isCollide(mousePos, nextChar))
						// 	{
						// 		characterIndex += 1;
						// 	}
						// 	else if (commonFunc::isCollide(mousePos, previousChar))
						// 	{
						// 		characterIndex -= 1;
						// 	}
						// 	if (characterIndex > TOTAL_CHAR-1)
						// 	{
						// 		characterIndex = 0;
						// 	}
						// 	if (characterIndex < 0)
						// 	{
						// 		characterIndex = TOTAL_CHAR-1;
						// 	}

						// 	for (auto& texture : playerIdleFrame) {
						// 	    SDL_DestroyTexture(texture);
						// 	}
						// 	for (auto& texture : playerFallFrame) {
						// 	    SDL_DestroyTexture(texture);
						// 	}
						// 	for (auto& texture : playerJumpFrame) {
						// 	    SDL_DestroyTexture(texture);
						// 	}

						// 	playerIdleFrame.clear();
						// 	playerJumpFrame.clear();
						// 	playerFallFrame.clear();

						// 	if (price[characterIndex] > 0)
						// 	{
						// 		selectButton.SetTex(TManager.blank);
						// 	}
						// 	else
						// 	{
						// 		selectButton.SetTex(TManager.select);
						// 	}
						// 	switch (characterIndex)
						// 	{
						// 	case CAT:
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty1.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty2.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty3.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty4.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty5.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty6.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty7.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty8.png"));

						// 		playerJumpFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty9.png"));
						// 		playerJumpFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty10.png"));

						// 		playerFallFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty11.png"));
						// 		playerFallFrame.emplace_back(window.Load("res/gfx/Player/Cat/kitty12.png"));
						// 		p.UpdateCurrFrame(playerIdleFrame[0]);
						// 		p.SetGravity(0.04f);
						// 		p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, SCREEN_HEIGHT/6 - p.GetCurrFrame().h/2));
						// 		p.numToSin = 0.f;
						// 		// std::cout << p.GetCurrFrame().w << " " << p.GetCurrFrame().h << std::endl;
						// 		break;
						// 	case BREAD:
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Bread/bread1.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Bread/bread2.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Bread/bread3.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Bread/bread4.png"));

						// 		playerJumpFrame.emplace_back(window.Load("res/gfx/Player/Bread/bread5.png"));
						// 		playerFallFrame.emplace_back(window.Load("res/gfx/Player/Bread/bread6.png"));
						// 		p.UpdateCurrFrame(playerIdleFrame[0]);
						// 		p.SetGravity(0.05f);
						// 		p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, SCREEN_HEIGHT/6 - p.GetCurrFrame().h/2));
						// 		p.numToSin = 0.f;
						// 		// std::cout << p.GetCurrFrame().w << " " << p.GetCurrFrame().h << std::endl;
						// 		break;
						// 	case HAMBURGER:
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger2.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger3.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger4.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger5.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger6.png"));
						// 		playerIdleFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger7.png"));

						// 		playerJumpFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger8.png"));
						// 		playerJumpFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger9.png"));

						// 		playerFallFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger10.png"));
						// 		playerFallFrame.emplace_back(window.Load("res/gfx/Player/Hamburger/burger11.png"));
						// 		p.UpdateCurrFrame(playerIdleFrame[0]);
						// 		p.SetGravity(0.05f);
						// 		p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, SCREEN_HEIGHT/6 - p.GetCurrFrame().h/2));
						// 		p.numToSin = 0.f;
						// 	break;
						// 	default:
						// 		break;
						// 	}
						// }
						// if (commonFunc::isCollide(mousePos,selectButton) && price[characterIndex] == 0)
						// {
						// 	currGameState = MAIN_MENU;
						// 	p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, 100));
						// }
						// if (commonFunc::isCollide(mousePos,selectButton) && price[characterIndex] > 0)
						// {
						// 	if (totalCoin >= price[characterIndex])
						// 	{
						// 		totalCoin -= price[characterIndex];
						// 		price[characterIndex] = 0;
						// 		std::ofstream outFileCoin("res/Coin.txt");
						// 		if (outFileCoin.is_open()) {
						// 			outFileCoin << totalCoin;
						// 			outFileCoin.close();
						// 		} else {
						// 			std::cerr << "Unable to open file for coin.\n";
    					// 		}

						// 		std::ofstream outFilePrice("res/Price.txt");
						// 		if (outFilePrice.is_open()) {
						// 			for (int i = 0; i < TOTAL_CHAR; i++)
						// 			{
						// 				outFilePrice << price[i] << std::endl;
						// 			}
						// 			outFilePrice.close();
						// 		} else {
						// 			std::cerr << "Unable to open file for price.\n";
    					// 		}
						// 		std::ifstream inFilePrice("res/Price.txt");
						// 		if (inFilePrice.is_open())
						// 		{
						// 			int n;
						// 			int i = 0;
						// 			while (inFilePrice >> n)
						// 			{
						// 				price[i++] = n;
						// 			}
						// 			inFilePrice.close();
						// 		}  else {
						// 			std::cerr << "Unable to open file for price.\n";
						// 		}
						// 	selectButton.SetTex(TManager.select);
						// 	}
						// }
						// break;
					case MODE_SELECTION:
						if(commonFunc::isCollide(mousePos, BManager.hellModeButton)) 
						{
							currGameState = PENDING;
							gameMode = HELL_MODE;
						}
						if(commonFunc::isCollide(mousePos, BManager.classicModeButton)) 
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
						if(commonFunc::isCollide(mousePos, BManager.OK_Button)) GameReset();
						if(commonFunc::isCollide(mousePos, BManager.menuButton))
						{
							GameReset();
							currGameState = MAIN_MENU;
						};
						break;
					case MUSIC_MANAGER:
						if(commonFunc::isCollide(mousePos, BManager.musicPlayerPlayButton))
						{
							if (musicPlayer.IsPlaying())
							{
								BManager.musicPlayerPlayButton.SetTex(TManager.musicPlayerMuteTexture);
								musicPlayer.Mute();
							}
							else if(musicPlayer.IsPlaying() == 0)
							{
								BManager.musicPlayerPlayButton.SetTex(TManager.musicPlayerPlayTexture);
								musicPlayer.UnMute();
							}
						}
						if (commonFunc::isCollide(mousePos, BManager.sfxPlayerButton))
						{
							if(SFX.IsPlaying())
							{
								BManager.sfxPlayerButton.SetTex(TManager.musicPlayerMuteTexture);
								SFX.Mute();
							}
							else
							{
								BManager.sfxPlayerButton.SetTex(TManager.musicPlayerPlayTexture);
								SFX.UnMute();
							}
						}

						if (commonFunc::isCollide(mousePos, BManager.PauseAndResumeMusic))
						{
							if (musicPlayer.IsPaused())
							{
								BManager.PauseAndResumeMusic.SetTex(TManager.pauseMusicTexture);
								musicPlayer.Resume();
							}
							else
							{
								BManager.PauseAndResumeMusic.SetTex(TManager.resumeMusicTexture);
								musicPlayer.Pause();
							}
						}
						if (commonFunc::isCollide(mousePos, BManager.bar1))
						{
							BManager.handleButton1.SetPos(Vector(mousePos.GetX()-6,BManager.handleButton1.GetPos().GetY()));
							musicVolume = (BManager.handleButton1.GetPos().GetX()-30) / 100.f;
							musicPlayer.SetVolume(musicVolume);
						}
						if (commonFunc::isCollide(mousePos, BManager.bar2))
						{
							BManager.handleButton2.SetPos(Vector(mousePos.GetX()-6,BManager.handleButton2.GetPos().GetY()));
							sfxVolume = (BManager.handleButton2.GetPos().GetX()-30) / 100.f;
							SFX.SetVolume(sfxVolume);
						}
						if (commonFunc::isCollide(mousePos, BManager.backwardButton))
						{
							musicPlayer.PreviousTrack();
						}
						if (commonFunc::isCollide(mousePos, BManager.forwardButton))
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
			playerIdleFrameIndex +=1;
			playerJumpFrameIndex +=1;
			playerFallFrameIndex +=1;
			coinFrameIndex += 1;
			spaceFrameIndex += 0.25f;
			if (playerIdleFrameIndex > p.playerIdleFrame.size()-1) playerIdleFrameIndex = 0;
			if (playerJumpFrameIndex > p.playerJumpFrame.size()-1) playerJumpFrameIndex = 0;
			if (playerFallFrameIndex > p.playerFallFrame.size()-1) playerFallFrameIndex = 0;
			if (coinFrameIndex > 4) coinFrameIndex = 0;
			if(spaceFrameIndex > 1) spaceFrameIndex = 0;
		}
		_cTime += 0.01f;
	}
	switch (currGameState)
	{
	case PLAY:
		if(p.inFly) p.SetTex(p.playerJumpFrame[playerJumpFrameIndex]);
		else p.SetTex(p.playerFallFrame[playerFallFrameIndex]);
		break;
	default:
		p.SetTex(p.playerIdleFrame[playerIdleFrameIndex]);
		break;
	}
	BManager.SpaceIMG.SetTex(TManager.spaceTexture[(int)spaceFrameIndex]);

	for (int i = 0; i < 4; i++)
	{
		Coins[i].SetTex(TManager.CoinTextures[coinFrameIndex]);
	}
	
	if (currGameState == MUSIC_MANAGER)
	{
		if (musicPlayer.GetVolume() != 0)
		{
			BManager.musicPlayerPlayButton.SetTex(TManager.musicPlayerPlayTexture);
		}
		if (SFX.GetVolume() != 0)
		{
			BManager.sfxPlayerButton.SetTex(TManager.musicPlayerPlayTexture);
		}
		BManager.handleButton1.SetPos(Vector(30.f+(musicPlayer.GetVolume()/128.f)*100, BManager.handleButton1.GetPos().GetY()));
		BManager.handleButton2.SetPos(Vector(30.f+(SFX.GetVolume()/128.f)*100, BManager.handleButton2.GetPos().GetY()));

		if (musicPlayer.IsPlaying() && BManager.handleButton1.GetPos().GetX() <31)
		{
				BManager.musicPlayerPlayButton.SetTex(TManager.musicPlayerMuteTexture);
				musicPlayer.Mute();
		}
		if (SFX.IsPlaying() && BManager.handleButton2.GetPos().GetX() <31)
		{
				BManager.sfxPlayerButton.SetTex(TManager.musicPlayerMuteTexture);
				SFX.Mute();
		}
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
		if (currGameState != PLAY && currGameState != SHOP)
		{
			p.Pending(1.f);
		}
		
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
		if (p.GetPos().GetX() > 30)
		{
			p.MoveLeft();
		}
		
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
				totalCoin += 1;
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
		}
	}

	if(currGameState == DIE)
	{
		if(deadTime == 0) deadTime = SDL_GetTicks();
		p.Update();
		if(p.GetPos().GetY() > 200 - p.GetCurrFrame().h)
		{
			p.SetPos(Vector(p.GetPos().GetX(),  200 - p.GetCurrFrame().h));
		}
		
		std::ofstream outFileCoin("res/Coin.txt");
		if (outFileCoin.is_open()) {
			outFileCoin << totalCoin;
			outFileCoin.close();
		} else {
			std::cerr << "Unable to open file for coin.\n";
    	}

		if (gameMode == CLASSIC_MODE)
		{
			std::ifstream inFile("res/HighScoreClassic.txt");
			if (inFile.is_open()) {
				inFile >> highScore;
				inFile.close();
			} else {
				std::cerr << "Unable to open file for reading high score. Assuming zero.\n";
			}
			if (currScore > highScore)
			{
				std::ofstream outFile("res/HighScoreClassic.txt");
				if (outFile.is_open()) {
					outFile << currScore;
					outFile.close();
				} else {
					std::cerr << "Unable to open file for writing high score.\n";
    			}
			}
		}
		else
		{
			std::ifstream inFile("res/HighScoreHell.txt");
			if (inFile.is_open()) {
				inFile >> highScore;
				inFile.close();
			} else {
				std::cerr << "Unable to open file for reading high score. Assuming zero.\n";
			}
			if (currScore > highScore)
			{
				std::ofstream outFile("res/HighScoreHell.txt");
				if (outFile.is_open()) {
					outFile << currScore;
					outFile.close();
				} else {
					std::cerr << "Unable to open file for writing high score.\n";
    			}
			}
		}
	}
}

void game::GameReset()
{
	p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2.f,100.f));
	pBG.SwitchState();

	pipeUp.clear();
	pipeDown.clear();
	Coins.clear();
	pBG.Reset();
	float pipeX = 240.f;
	for (int i = 0; i<4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), TManager.pipesTexture[0], 1));
		float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), TManager.pipesTexture[1], 0));
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
	p.numToSin = 0;
}