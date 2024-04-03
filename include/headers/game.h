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
    window Window;
    Vector mousePos;
    //Textures
    SDL_Texture* playerTexture[3] = {NULL,NULL,NULL};
    SDL_Texture* backgroundTexture[2] = {NULL, NULL};
    SDL_Texture* groundTexture = NULL;
    SDL_Texture* UI_OkButton = NULL;
    SDL_Texture* pipesTexture[2] = {NULL, NULL};
    //Objects
    std::vector<ground> base;
    std::vector<background> bg;
    std::vector<Pipe> pipeUp;
    std::vector<Pipe> pipeDown;

    player p;
    button OK_button;
    
    //Time
    float _cTime = 0.0f;
    float _timeStep = 0.1f;
    int index = 0;
    SDL_Event event;

    int gameState = PENDING;

public:
    game();
    bool isQuit(){return gameState == QUIT;};
    int getRefreshRate(){return Window.GetRefreshRate();};
    void Run();
    void Update();
    void Render();
    void Clean();
    void GameReset();
    
};

