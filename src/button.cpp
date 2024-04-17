#include<headers/button.h>

Button::Button(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

ButtonManager::ButtonManager(TextureManager &p_tm)
			  :TManager(&p_tm)
{}

void ButtonManager::LoadButton()
{
	OK_Button = Button(Vector(SCREEN_WIDTH/6 - 20, 180.f), TManager->OK_ButtonTexture);
	startButton  = Button(Vector(SCREEN_WIDTH/6 - 20, 148.f), TManager->startTexture);
	classicModeButton  = Button(Vector(SCREEN_WIDTH/6 - 20,148.f), TManager->classicModeTexture);
	hellModeButton  = Button(Vector(SCREEN_WIDTH/6 - 20,170.f), TManager->hellModeTexture);
	pauseButton  = Button(Vector(5.f,5.f), TManager->pauseTexture);
	playButton  = Button(Vector(5.f,5.f), TManager->playTexture);
	menuButton  = Button(Vector(SCREEN_WIDTH/6 - 20,160.f), TManager->menuTexture);
	SpaceIMG = Button(Vector(SCREEN_WIDTH/6 - 32,110), TManager->spaceTexture[0]);
	PauseAndResumeMusic = Button(Vector(90,130), TManager->pauseMusicTexture);
	musicPlayerButton  = Button(Vector(SCREEN_WIDTH/3 - 5 - 16 ,SCREEN_HEIGHT/3 - 5- 16), TManager->musicPlayerTexture);
	musicPlayerPlayButton = Button(Vector(18,130), TManager->musicPlayerPlayTexture);
	sfxPlayerButton = Button(Vector(18,150), TManager->musicPlayerPlayTexture);
	forwardButton = Button(Vector(110,130), TManager->forwardTexture);
	backwardButton = Button(Vector(70, 130), TManager->backwardTexture);
	shopButton = Button(Vector(SCREEN_WIDTH/3 - 5 - 16,SCREEN_HEIGHT/3 - 5 - 40), TManager->shopTexture);
	handleButton1 = Button(Vector((130-30)/2+30-6,165), TManager->handle);
	handleButton2 = Button(Vector((130-30)/2+30-6,165+12), TManager->handle);

	bar1 = Button(Vector(30, 168),TManager->bar);
	bar2 = Button(Vector(30, 180),TManager->bar);

	nextChar = Button(Vector(110, SCREEN_HEIGHT/6 -8), TManager->nextChar);
	previousChar = Button(Vector(18, SCREEN_HEIGHT/6-8), TManager->previousChar);
	selectButton = Button(Vector(SCREEN_WIDTH/6-20, 180), TManager->select);
}

void ButtonManager::Render(Window& window, int &currGameState, Uint32 deadTime)
{
	switch (currGameState)
	{
	case MAIN_MENU:
		window.Render(startButton);
		window.Render(musicPlayerButton);
		window.Render(shopButton);
		break;
	case MODE_SELECTION:
		window.Render(classicModeButton);
		window.Render(hellModeButton);
		break;
	case PENDING:
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
		}
		break;
	case MUSIC_MANAGER:
		window.Render(musicPlayerPlayButton);
		window.Render(sfxPlayerButton);
		window.Render(PauseAndResumeMusic);
		window.Render(backwardButton);
		window.Render(forwardButton);
		window.Render(bar1);
		window.Render(bar2);
		window.Render(handleButton1);
		window.Render(handleButton2);
		break;
	case SHOP:
		window.Render(previousChar);
		window.Render(nextChar);
		window.Render(selectButton);
		break;
	default:
		break;
	}
}