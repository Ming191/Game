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
	AManager = AudioManager(BManager, TManager, SFX, musicPlayer);
	AManager.Init();

	base.Init(TManager);
	p = Player(Vector(SCREEN_WIDTH/6-10,100), window.Load("res/gfx/Player/Cat/kitty1.png") , SFX, TManager);
	pipeLink.Init(TManager);
	pBG = ParallaxBG(window);
	foreGround.Init(window);

	commonFunc::CoinIn();
}

void game::Clean()
{
	window.Clean();
}

void game::Render()
{
	window.Clear();
	pBG.Render();
	pipeLink.Render(window);
	base.Render(window);
	foreGround.Render(window);
	TManager.Render(timer.deadTime);
	BManager.Render(window, timer.deadTime, p);
	TManager.RenderText(timer.deadTime, musicPlayer, price);
	if(currentGameState != MUSIC_MANAGER) window.RenderRotate(p, p.GetPos(), 0);
	window.Display();
}

void game::HandleEvents()
{	
	while (SDL_PollEvent(&event))
	{
		if (currentGameState == MUSIC_MANAGER)
		{
			if ((event.type == SDL_MOUSEMOTION )&& (event.motion.state & SDL_BUTTON_LMASK))
			{
				if ((commonFunc::isCollide(mousePos,BManager.handleButton1) || commonFunc::isCollide(mousePos, BManager.bar1)) && (mousePos.GetX()>=30 && mousePos.GetX() <= 130))
				{
					AManager.DragAndDropMusic(mousePos);
				}
				if ((commonFunc::isCollide(mousePos,BManager.handleButton2) || commonFunc::isCollide(mousePos, BManager.bar2)) && (mousePos.GetX()>=30 && mousePos.GetX() <= 130))
				{
					AManager.DragAndDropSFX(mousePos);
				}
			}
		}
		switch (event.type)
		{
			case SDL_QUIT:
				currentGameState = QUIT;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					switch (currentGameState)
					{
					case PLAY:
						currentGameState = PAUSE;
						break;
					case PAUSE:
						currentGameState = PLAY;
						break;
					case MUSIC_MANAGER:
						currentGameState = MAIN_MENU;
						break;
					default:
						break;
					}
				} 
				else if(event.key.keysym.sym == SDLK_SPACE)
				{
					switch (currentGameState)
					{
					case PLAY:
						p.Fly();
						break;
					case PENDING:
						currentGameState = PLAY;
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
					switch (currentGameState)
					{
					case MAIN_MENU:
						if (commonFunc::isCollide(mousePos, BManager.startButton))
						{
							currentGameState = MODE_SELECTION;
						}
						if (commonFunc::isCollide(mousePos, BManager.musicPlayerButton))
						{
							currentGameState = MUSIC_MANAGER;
						}
						if (commonFunc::isCollide(mousePos, BManager.shopButton))
						{
							commonFunc::PriceIn();
							currentGameState = SHOP;
							p.SetPosMiddle();
						}
						break;
					case SHOP:
						if (commonFunc::isCollide(mousePos, BManager.nextChar) || commonFunc::isCollide(mousePos, BManager.previousChar))
						{
							if (commonFunc::isCollide(mousePos, BManager.nextChar))
							{
								p.NextChar();
							}
							else p.PreviousChar();

							p.SwitchCharacter();
						}
						if (commonFunc::isCollide(mousePos,BManager.selectButton) && price[CharacterIndex] == 0)
						{
							currentGameState = MAIN_MENU;
							p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, 100));
						}
						if (commonFunc::isCollide(mousePos,BManager.selectButton) && price[CharacterIndex] > 0)
						{
							if (totalCoin >= price[CharacterIndex])
							{
								totalCoin -= price[CharacterIndex];
								price[CharacterIndex] = 0;
								commonFunc::CoinOut();
								commonFunc::PriceOut();
								commonFunc::PriceIn();
								BManager.selectButton.SetTex(TManager.select);
							}
						}
						break;
					case MODE_SELECTION:
						if(commonFunc::isCollide(mousePos, BManager.hellModeButton)) 
						{
							currentGameState = PENDING;
							gameMode = HELL_MODE;
						}
						if(commonFunc::isCollide(mousePos, BManager.classicModeButton)) 
						{
							currentGameState = PENDING;
							gameMode = CLASSIC_MODE;
						}
						break;
					case PENDING:
						currentGameState = PLAY;	
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
							currentGameState = MAIN_MENU;
						};
						break;
					case MUSIC_MANAGER:
						AManager.HandleClickEvent(mousePos);		
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

	if(currentGameState != DIE && currentGameState != PAUSE)
	{
		if (currentGameState != PLAY && currentGameState != SHOP)
		{
			p.Pending(1.f);
		}
		timer.Update(p);
		base.Update();
		foreGround.Update();
		pBG.Update();
	}

	timer.PlayerFrameUpdate(p);
	timer.SpaceFrameUpdate(BManager, TManager);
	timer.CoinFrameUpdate(pipeLink, TManager);

	switch (currentGameState)
	{
	case MUSIC_MANAGER:
		AManager.Update();
		break;
	case PLAY:
		p.Update();
		pipeLink.RestartLoop();
		pipeLink.Update(gameMode);
		currentGameState = pipeLink.CheckCollision(p,SFX);
		timer.IsScored();
		pipeLink.CheckPlayerPass(SFX, timer.scored, p);
		base.CheckCollision(p,SFX);
		break;
	case DIE:
		p.Update();
		commonFunc::CoinOut();
		commonFunc::HighScoreInOut(gameMode == CLASSIC_MODE);
		break;
	default:
		break;
	}
	if (currentGameState == DIE)
	{
		timer.UpdateDeadTime();
	}
}

void game::GameReset()
{
	p.Reset();
	pBG.SwitchState();
	pBG.Reset();
	pipeLink.Reset(TManager);
	currentGameState = PENDING;
	currentScore = 0;
	timer.Reset();
	TManager.ResetFlash();
	p.numToSin = 0;
}