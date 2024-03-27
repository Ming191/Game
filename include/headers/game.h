#pragma once

#include<iostream>
#include<vector>

#include<headers/window.h>
#include<headers/entity.h>
#include<headers/player.h>
#include<headers/ground.h>
#include<headers/background.h>
#include<headers/commonFunc.h>


class game
{
private:
    window Window;
    //Textures
    SDL_Texture* playerTexture[3] = {NULL,NULL,NULL};
    SDL_Texture* backgroundTexture[2] = {NULL, NULL};
    SDL_Texture* groundTexture = NULL;
    //Objects
    std::vector<ground> base;
    std::vector<background> bg;
    player p;
    
    //Time
    float _cTime = 0.0f;
    float _timeStep = 0.1f;
    int index = 0;
    SDL_Event event;

public:
    game();
    bool isBirdDead = false;
    bool quit = false;
    bool start = false;
    bool isQuit(){return quit;};
    int getRefreshRate(){return Window.GetRefreshRate();};
    void run();
    void update();
    void render();
    void clean();
    
};

