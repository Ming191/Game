#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>


#include<headers/entity.h>
#include<headers/player.h>
#include<headers/bg.h>


using namespace std;

class game
{
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    player p;
    bg bg;

    SDL_Event evnt;

    const int SCREEN_WIDTH = 256;
    const int SCREEN_HEIGHT = 256;

    SDL_Rect src;
	SDL_Rect dst;
public:
    bool isRunning = false;
    game();
    ~game();
    bool running(){return isRunning;};
    bool initGraphic();
    void handleEvents();
    void update();
    void render();
    void clean();
    
};

