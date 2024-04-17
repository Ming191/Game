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
    
    handle = window->Load("res/gfx/handle.png");
    bar = window->Load("res/gfx/bar.png");
    nextChar = window->Load("res/gfx/nextChar.png");
    previousChar = window->Load("res/gfx/previousChar.png");
    select = window->Load("res/gfx/select.png");

}