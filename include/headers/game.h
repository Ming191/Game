#pragma once

#include<headers/window.h>
#include<headers/player.h>
#include<headers/ground.h>
#include<headers/background.h>
#include<headers/button.h>
#include<headers/pipe.h>
#include<headers/Coin.h>
#include<headers/commonFunc.h>
#include<headers/sfx.h>
class game
{
private:
    Window window;
    Vector mousePos;
    int gameMode;
    //Textures
    SDL_Texture* titleTexture = NULL;
    SDL_Texture* modeSeclectionTexture = NULL;
    SDL_Texture* classicModeTexture = NULL;
    SDL_Texture* hellModeTexture = NULL;
    SDL_Texture* pauseTexture = NULL;
    SDL_Texture* startTexture = NULL;
    SDL_Texture* playTexture = NULL;
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* gameOverTexture = NULL;
    SDL_Texture* spaceTexture[2] = {NULL, NULL};

    SDL_Texture* thanksIMG = NULL;
    SDL_Texture* cloud_bgTexture = NULL;

    SDL_Texture* musicPlayerPanelTexture = NULL;
    SDL_Texture* scorePanelTexture = NULL;
    SDL_Texture* flashTexture = NULL;
    
    SDL_Texture* groundTexture = NULL;
    SDL_Texture* OK_ButtonTexture = NULL;
    SDL_Texture* pipesTexture[2] = {NULL, NULL};
    SDL_Texture* medalTexture[3] = {NULL, NULL, NULL};

    SDL_Texture* musicPlayerTexture = NULL;
    SDL_Texture* musicPlayerPlayTexture = NULL;
    SDL_Texture* musicPlayerMuteTexture = NULL;
    SDL_Texture* shopTexture = NULL;

    SDL_Texture* forwardTexture = NULL;
    SDL_Texture* backwardTexture = NULL;

    SDL_Texture* shopPanel;

    //Objects
    std::vector<Ground> base;
    std::vector<Background> foreGround;
    std::vector<Pipe> pipeUp;
    std::vector<Pipe> pipeDown;

    std::vector<SDL_Texture*> playerIdleFrame;
    std::vector<SDL_Texture*> playerJumpFrame;
    std::vector<SDL_Texture*> playerFallFrame;

    Player p;
    Button OK_Button;
    Button startButton;
    Button modeSelectionButton;
    Button classicModeButton;
    Button hellModeButton;
    Button pauseButton;
    Button playButton;
    Button menuButton;
    Button musicPlayerButton;
    Button musicPlayerPlayButton;
    Button sfxPlayerButton;
    Button shopButton;
    Button handleButton;
    Button bar;
    Button nextChar;

    Entity SpaceIMG;

    Button forwardButton;
    Button backwardButton;

    SDL_Texture* CoinTextures[5] = {NULL, NULL, NULL, NULL, NULL};
    std::vector<Coin> Coins;
    
    //Time
    float _cTime = 0.0f;
    float _timeStep = 0.1f;
    int playerFrameIndex = 0;

    int characterIndex = CAT;
    int playerIdleFrameIndex = 0;
    int playerJumpFrameIndex = 0;
    int playerFallFrameIndex = 0;
    int coinFrameIndex = 0;
    float spaceFrameIndex = 0;
    SDL_Event event;

    Uint32 deadTime = 0;
    Uint32 hitTime[4] = {0,0,0,0};

    float scoreAccumulator = 0.f;
    int currScore = 0;
    bool scored = false;
    int currGameState = MAIN_MENU;
    int highScore;
    int totalCoin;

    int flashAlpha = 255;

    MusicPlayer musicPlayer;
    SoundEffect SFX;

    float masterVolume = 0.5f;

    ParallaxBG pBG;
public:
    game();
    bool isQuit(){return currGameState == QUIT;};
    int getRefreshRate(){return window.GetRefreshRate();};
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void GameReset();
};

