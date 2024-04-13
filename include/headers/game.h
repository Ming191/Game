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
#include<sstream>
class game
{
private:
    Window window;
    Vector mousePos;
    int gameMode;
    //Textures
    SDL_Texture* titleTexture = NULL;
    SDL_Texture* modeSeclectionTexture = NULL;
    SDL_Texture* optionsTexture = NULL;
    SDL_Texture* classicModeTexture = NULL;
    SDL_Texture* hellModeTexture = NULL;
    SDL_Texture* pauseTexture = NULL;
    SDL_Texture* startTexture = NULL;
    SDL_Texture* playTexture = NULL;
    SDL_Texture* handTexture = NULL;
    SDL_Texture* getReadyTexture = NULL;
    SDL_Texture* BW_BirdTexture = NULL;
    SDL_Texture* tapTexture = NULL;
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* gameOverTexture = NULL;

    SDL_Texture* musicPlayerPanelTexture = NULL;
    SDL_Texture* scorePanelTexture = NULL;
    SDL_Texture* flashTexture = NULL;
    
    SDL_Texture* playerTexture[3] = {NULL,NULL,NULL};
    SDL_Texture* BackgroundTexture[2] = {NULL, NULL};
    SDL_Texture* groundTexture = NULL;
    SDL_Texture* OK_ButtonTexture = NULL;
    SDL_Texture* pipesTexture[2] = {NULL, NULL};
    SDL_Texture* medalTexture[3] = {NULL, NULL, NULL};

    SDL_Texture* musicPlayerTexture = NULL;
    SDL_Texture* musicPlayerPlayTexture = NULL;
    SDL_Texture* musicPlayerMuteTexture = NULL;

    SDL_Texture* forwardTexture = NULL;
    SDL_Texture* backwardTexture = NULL;
    //Objects
    std::vector<Ground> base;
    std::vector<Background> bg;
    std::vector<Pipe> pipeUp;
    std::vector<Pipe> pipeDown;

    Player p;
    Button OK_Button;
    Button startButton;
    Button optionsButton;
    Button modeSelectionButton;
    Button classicModeButton;
    Button hellModeButton;
    Button pauseButton;
    Button playButton;
    Button menuButton;
    Button musicPlayerButton;
    Button musicPlayerPlayButton;

    Button forwardButton;
    Button backwardButton;

    SDL_Texture* CoinTextures[5] = {NULL, NULL, NULL, NULL, NULL};
    std::vector<Coin> Coins;
    
    //Time
    float _cTime = 0.0f;
    float _timeStep = 0.1f;
    int playerFrameIndex = 0;
    int coinFrameIndex = 0;
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
    SoundEffect Jump;
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

