#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class window
{
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    const int SCREEN_WIDTH = 432;
    const int SCREEN_HEIGHT = 768; 
public:
    void CreateWindow(const char* title);
    int  GetRefreshRate();
    void Display();
    void Clear();
    void Clean();

};