#include <headers/textureManager.h>
#include "textureManager.h"

TextureManager::TextureManager(Window &p_window)
                :window(&p_window)
{
}

void TextureManager::LoadTexture()
{	
    titleTexture = window->Load("res/gfx/FlappyBirdText.png");
	gameOverTexture = window->Load("res/gfx/GameOverText.png");
	scorePanelTexture = window->Load("res/gfx/ScorePanel.png");

	groundTexture = window->Load("res/gfx/Ground2.png");
    OK_ButtonTexture = window->Load("res/gfx/OkButton.png");
	startTexture = window->Load("res/gfx/StartButton.png");
	classicModeTexture = window->Load("res/gfx/ClassicMode.png");
	hellModeTexture = window->Load("res/gfx/HellMode.png");
	pauseTexture = window->Load("res/gfx/PauseButton.png");
	playTexture = window->Load("res/gfx/PlayButton.png");
	menuTexture = window->Load("res/gfx/MenuButton.png");

    medalTexture[0] = window->Load("res/gfx/Bronze.png");
	medalTexture[1] = window->Load("res/gfx/Silver.png");
	medalTexture[2] = window->Load("res/gfx/Gold.png");

	CoinTextures[0] = window->Load("res/gfx/Coin1.png");
	CoinTextures[1] = window->Load("res/gfx/Coin2.png");
	CoinTextures[2] = window->Load("res/gfx/Coin3.png");
	CoinTextures[3] = window->Load("res/gfx/Coin4.png");
	CoinTextures[4] = window->Load("res/gfx/Coin5.png");

	spaceTexture[0] = window->Load("res/gfx/Space1.png");
	spaceTexture[1] = window->Load("res/gfx/Space2.png");

    pipesTexture[0] = window->Load("res/gfx/PipeUpSilver.png");
	pipesTexture[1] = window->Load("res/gfx/PipeDownSilver.png");

    pauseMusicTexture = window->Load("res/gfx/PauseMusic.png");
	resumeMusicTexture = window->Load("res/gfx/ResumeMusic.png");

    musicPlayerPanelTexture = window->Load("res/gfx/musicPlayerPanel.png");
	musicPlayerTexture = window->Load("res/gfx/musicPlayer.png");

    musicPlayerPlayTexture = window->Load("res/gfx/Sound.png");
	musicPlayerMuteTexture = window->Load("res/gfx/SoundMute.png");

    forwardTexture = window->Load("res/gfx/forward.png");
	backwardTexture = window->Load("res/gfx/backward.png");

    shopTexture = window->Load("res/gfx/Shop.png");
    shopPanel = window->Load("res/gfx/shopPanel.png");

    totalCoinTexture = window->Load("res/gfx/totalCoin.png");

    blank = window->Load("res/gfx/blank.png");
	select = window->Load("res/gfx/select.png");
    flashTexture = window->Flash();

    thanksIMG = window->Load("res/gfx/Thanks.png");

    kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty1.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty2.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty3.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty4.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty5.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty6.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty7.png"));
	kittenIdleFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty8.png"));

	kittenJumpFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty9.png"));
	kittenJumpFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty10.png"));

	kittenFallFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty11.png"));
	kittenFallFrame.emplace_back(window->Load("res/gfx/Player/Cat/kitty12.png"));

	kitten.emplace_back(kittenIdleFrame);
	kitten.emplace_back(kittenJumpFrame);
	kitten.emplace_back(kittenFallFrame);

	breadIdleFrame.emplace_back(window->Load("res/gfx/Player/Bread/bread1.png"));
	breadIdleFrame.emplace_back(window->Load("res/gfx/Player/Bread/bread2.png"));
	breadIdleFrame.emplace_back(window->Load("res/gfx/Player/Bread/bread3.png"));
	breadIdleFrame.emplace_back(window->Load("res/gfx/Player/Bread/bread4.png"));
	breadJumpFrame.emplace_back(window->Load("res/gfx/Player/Bread/bread5.png"));
	breadJumpFrame.emplace_back(window->Load("res/gfx/Player/Bread/bread6.png"));

	bread.emplace_back(breadIdleFrame);
	bread.emplace_back(breadJumpFrame);
	bread.emplace_back(breadJumpFrame);

	burgerIdleFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger2.png"));
	burgerIdleFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger3.png"));
	burgerIdleFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger4.png"));
	burgerIdleFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger5.png"));
	burgerIdleFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger6.png"));
	burgerIdleFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger7.png"));
	burgerJumpFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger8.png"));
	burgerJumpFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger9.png"));
	burgerFallFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger10.png"));
	burgerFallFrame.emplace_back(window->Load("res/gfx/Player/Hamburger/burger11.png"));
    
	burger.emplace_back(burgerIdleFrame);
	burger.emplace_back(burgerJumpFrame);
	burger.emplace_back(burgerFallFrame);

    handle = window->Load("res/gfx/handle.png");
    bar = window->Load("res/gfx/bar.png");
    nextChar = window->Load("res/gfx/nextChar.png");
    previousChar = window->Load("res/gfx/previousChar.png");
    select = window->Load("res/gfx/select.png");

}

void TextureManager::Render(Uint32 &deadTime)
{
	switch (currentGameState)
	{
	case MAIN_MENU:
		window->RenderScale(titleTexture, Vector(SCREEN_WIDTH/8 - 110/2, 20.f), 4);
		window->Render(totalCoinTexture, Vector(SCREEN_WIDTH/3 -5 - 40, 5));
		window->RenderScale(thanksIMG, Vector(0.f,300.f), 2);
		break;
	case MODE_SELECTION:
		window->RenderScale(titleTexture, Vector(SCREEN_WIDTH/8 - 110/2, 20.f), 4);
		break;
	case DIE:
		if (SDL_GetTicks() - deadTime > 800)
		{
			window->RenderScale(gameOverTexture, Vector(SCREEN_WIDTH/6 - 192/4 - 10, 48.f), 2);
			window->Render(scorePanelTexture, Vector(SCREEN_WIDTH/6-113/2, 80.f));
			if (currentScore > 10)
			{
				window->Render(medalTexture[0], Vector(29,101));
			} else if(currentScore > 50)
			{
				window->Render(medalTexture[1], Vector(29,101));
			} else if(currentScore > 100)
			{
				window->Render(medalTexture[2], Vector(29,101));
			}
		}
		else RenderFlash();
		break;
	case MUSIC_MANAGER:
		window->Render(musicPlayerPanelTexture,Vector(0, 80));
		break;
	case SHOP:
		window->RenderScale(shopPanel, Vector(SCREEN_WIDTH/12-24, SCREEN_HEIGHT/12-24),6);
		window->Render(totalCoinTexture, Vector(SCREEN_WIDTH/3 -5 - 40, 5));
	default:
		break;
	}

}

void TextureManager::RenderFlash()
{
	if (flashAlpha > 0)
	{
		SDL_SetTextureAlphaMod(flashTexture, flashAlpha);
		window->Render(flashTexture, Vector(0,0));
		flashAlpha -= 5;
	}
}

void TextureManager::ResetFlash()
{
	flashAlpha = 255;
}

void TextureManager::RenderText(Uint32 &deadTime, MusicPlayer& musicPlayer, std::vector<int> price)
{
	std::string currScoreS = std::to_string(currentScore);
	if(currScoreS.length() < 2) currScoreS = "0" + currScoreS;

	std::string highScoreS = std::to_string(highScore);
	if(highScoreS.length() < 2) highScoreS = "0" + highScoreS;
	switch (currentGameState)
	{
	case MAIN_MENU:
		window->RenderText(Vector(330, 16), std::to_string(totalCoin), "res/font/monogram-extended.ttf", 16, white, 0);
		break;
	case DIE:
		if (SDL_GetTicks() - deadTime > 800)
		{
			window->RenderText(Vector(290.f,280.f), currScoreS, "res/font/monogram-extended.ttf", 16 , white,0);
			window->RenderText(Vector(290.f,350.f), highScoreS, "res/font/monogram-extended.ttf", 16 , white,0);
		}
		break;
	case MUSIC_MANAGER:
		window->RenderText(Vector(56,320), musicPlayer.GetTitle(),"res/font/monogram-extended.ttf", 16, white, 0);
	    window->RenderText(Vector(115,390), "Music" ,"res/font/monogram-extended.ttf", 16, white, 0);
	    window->RenderText(Vector(115,450), "SFX" ,"res/font/monogram-extended.ttf", 16, white, 0);
		break;
	case SHOP:
		window->RenderText(Vector(330, 16), std::to_string(totalCoin), "res/font/monogram-extended.ttf", 16, white, 0);
		if (price[CharacterIndex] > 0)
		{
			window->RenderText(Vector(190,538), std::to_string(price[CharacterIndex]), "res/font/monogram-extended.ttf", 16, white, 0);
		}
	default:
		break;
	}
}