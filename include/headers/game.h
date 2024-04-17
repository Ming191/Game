#pragma once

#include<headers/window.h>
#include<headers/player.h>
#include<headers/ground.h>
#include<headers/background.h>
#include<headers/button.h>
#include<headers/commonFunc.h>
#include<headers/textureManager.h>
#include<headers/sfx.h>
#include<headers/AudioManager.h>
#include<headers/PipeLink.h>
class game
{
private:
    Window window;
    Vector mousePos;
    int gameMode = 0;
    //Objects
    std::vector<int> price = {0,0,0};
    Foreground foreGround;

    Player p;
    
    //Time
    float _cTime = 0.0f;
    float _timeStep = 0.1f;

    int characterIndex = CAT;
    int playerIdleFrameIndex = 0;
    int playerJumpFrameIndex = 0;
    int playerFallFrameIndex = 0;
    int coinFrameIndex = 0;
    float spaceFrameIndex = 0;
    SDL_Event event;

    Uint32 deadTime = 0;

    float scoreAccumulator = 0.f;
    int currScore = 0;
    bool scored = false;
    int currGameState = MAIN_MENU;
    int highScore;
    int totalCoin;

    int flashAlpha = 255;

    MusicPlayer musicPlayer;
    SoundEffect SFX;

    ParallaxBG pBG;
    TextureManager TManager;
    ButtonManager BManager;
    AudioManager AManager;
    PipeLink pipeLink;
    GroundLinked base;
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

