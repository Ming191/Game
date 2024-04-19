#pragma once

#include<headers/window.h>
#include<headers/player.h>
#include<headers/ground.h>
#include<headers/background.h>
#include<headers/button.h>
#include<headers/commonFunc.h>
#include<headers/textureManager.h>
#include<headers/AudioManager.h>
#include<headers/PipeLink.h>
#include<headers/Timer.h>

class game
{
private:
    Window window;
    Vector mousePos;
    int gameMode = 0;
    //Objects
    TextureManager TManager;
    Player          p;
    SDL_Event       event;
    Music           music;
    SoundEffect     SFX;
    ParallaxBG      pBG;
    Foreground      foreGround;
    TextureManager  TManager;
    ButtonManager   BManager;
    AudioManager    AManager;
    PipeLinked      pipeLink;
    GroundLinked    base;
    Timer           timer;
public:
    game();
    bool isQuit(){return currentGameState == QUIT;};
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void GameReset();
};

