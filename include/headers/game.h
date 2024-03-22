#pragma once

#include<headers/window.h>
#include<iostream>


#include<headers/entity.h>
#include<headers/player.h>
#include<headers/bg.h>


class game
{
private:
    window Window;

    player p;
    bg bg;

    SDL_Event event;

    SDL_Rect src;
	SDL_Rect dst;
public:
    bool isRunning = true;
    game();
    ~game();
    bool running(){return isRunning;};
    bool initGraphic();
    void handleEvents();
    void update();
    void render();
    void clean();
    
};

