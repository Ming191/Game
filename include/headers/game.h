#pragma once

#include<iostream>
#include<vector>

#include<headers/window.h>
#include<headers/entity.h>
#include<headers/player.h>
#include<headers/ground.h>
#include<headers/background.h>
#include<headers/button.h>
#include<headers/pipe.h>
#include<headers/commonFunc.h>

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
    SDL_Texture* playerTexture[3] = {NULL,NULL,NULL};
    SDL_Texture* BackgroundTexture[2] = {NULL, NULL};
    SDL_Texture* groundTexture = NULL;
    SDL_Texture* OK_ButtonTexture = NULL;
    SDL_Texture* pipesTexture[2] = {NULL, NULL};
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
    
    //Time
    float _cTime = 0.0f;
    float _timeStep = 0.1f;
    int index = 0;
    SDL_Event event;

   float scoreAccumulator = 0.f;
    int currScore = 0;
    bool scored = false;

    int currGameState = MAIN_MENU;

public:
    game();
    bool isQuit(){return currGameState == QUIT;};
    int getRefreshRate(){return window.GetRefreshRate();};
    void Run();
    void Update();
    void Render();
    void Clean();
    void GameReset();
    
};

