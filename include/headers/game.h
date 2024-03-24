#pragma once

#include<headers/window.h>
#include<iostream>

#include<headers/entity.h>
#include<headers/player.h>
#include<headers/commonFunc.h>


class game
{
private:
    window Window;
    // bg bg;
    //Texture
    SDL_Texture* playerTexture = NULL;
    player p;

    SDL_Event event;

public:
    bool isBirdDead = false;
    bool isRunning = true;
    bool running(){return isRunning;};
    int getRefreshRate(){return Window.GetRefreshRate();};
    bool initGraphic();
    void run();
    void update();
    void render();
    void clean();
    
};

