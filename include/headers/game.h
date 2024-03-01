#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>

using namespace std;

class game
{
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    bool isRunning = false;
    SDL_Event evnt;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 400;
public:
    game();
    ~game();
    bool running(){return isRunning;};
    bool initGraphic();
    void handleEvents();
    void update();
    void render();
    void clean();
    
};

