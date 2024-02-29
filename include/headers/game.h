#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>

class game
{
private:
    int cnt = 0;
    SDL_Window* gWindow = nullptr;
    SDL_Renderer* gRenderer = nullptr;
    bool isRunning = false;

    const int WIDTH = 800;
    const int HEIGHT = 1000;
public:

    bool running() {return isRunning;};
    void init(const char* title);
    void handleEvent();
    void update();
    void render();
    void clean();
};

