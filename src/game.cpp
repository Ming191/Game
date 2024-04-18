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

	base = GroundLinked(TManager);
	base.Init();
	p = Player(Vector(SCREEN_WIDTH/6-10,100), window.Load("res/gfx/Player/Cat/kitty1.png") , SFX, TManager);
	
	pipeLink.Init(TManager);

//	---BackgroundAndForeGroundInit---
	pBG = ParallaxBG(window, currScore);
	foreGround.Init(window);

//	---Shop---
	commonFunc::CoinIn(totalCoin);
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

	pBG.Render();
	pipeLink.Render(window);
	
	base.Render(window);
	TManager.Render(currGameState, currScore, timer.deadTime);
	BManager.Render(window,currGameState, timer.deadTime);
	
	switch (currGameState)
	{
	case MAIN_MENU:
		window.RenderText(Vector(330, 16), std::to_string(totalCoin), "res/font/monogram-extended.ttf", 16, white, 0);
		break;
	case DIE:
		if (SDL_GetTicks() - timer.deadTime > 800)
		{
			window.RenderText(Vector(290.f,280.f), currScoreS, "res/font/monogram-extended.ttf", 16 , white,0);
			window.RenderText(Vector(290.f,350.f), highScoreS, "res/font/monogram-extended.ttf", 16 , white,0);
		}
		break;
	case MUSIC_MANAGER:
		window.RenderText(Vector(56,320), musicPlayer.GetTitle(),"res/font/monogram-extended.ttf", 16, white, 0);
	    window.RenderText(Vector(115,390), "Music" ,"res/font/monogram-extended.ttf", 16, white, 0);
	    window.RenderText(Vector(115,450), "SFX" ,"res/font/monogram-extended.ttf", 16, white, 0);
		break;
	case SHOP:
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
							commonFunc::PriceIn(price);
							currGameState = SHOP;
							p.SetPos(Vector(SCREEN_WIDTH/6 - p.GetCurrFrame().w/2, SCREEN_HEIGHT/6 - p.GetCurrFrame().h/2));
						}
						break;
					// case SHOP:
						// if (commonFunc::isCollide(mousePos, nextChar) || commonFunc::isCollide(mousePos, previousChar))
						// {
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

	if(currGameState != DIE && currGameState != PAUSE)
	{
		if (currGameState != PLAY && currGameState != SHOP)
		{
			p.Pending(1.f);
		}
		timer.Update(p);
		base.Update();
		foreGround.Update(window);
		pBG.Update();
	}

	timer.PlayerFrameUpdate(p, currGameState);
	timer.SpaceFrameUpdate(BManager, TManager);
	timer.CoinFrameUpdate(pipeLink, TManager);
	
	if (currGameState == MUSIC_MANAGER)
	{
		AManager.Update();
	}
	
	if (currGameState == PLAY)
	{
		p.MoveLeft();
		p.Update();
		pipeLink.RestartLoop();
		pipeLink.Update(gameMode);
		pipeLink.CheckCollision(p,SFX, currGameState);
		pipeLink.CheckPlayerPass(SFX, currScore, totalCoin, timer.scored, currGameState, p);
		base.CheckCollision(p,currGameState,SFX);
		timer.IsScored();
	}

	if(currGameState == DIE)
	{
		timer.UpdateDeadTime();
		p.Update();
		commonFunc::CoinOut(totalCoin);
		commonFunc::HighScoreInOut(highScore, currScore, gameMode == CLASSIC_MODE);
	}
}

void game::GameReset()
{
	p.Reset();
	pBG.SwitchState();
	pBG.Reset();
	pipeLink.Reset(TManager);
	currGameState = PENDING;
	currScore = 0;
	timer.Reset();
	TManager.ResetFlash();
	p.numToSin = 0;
}