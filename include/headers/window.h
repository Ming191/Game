#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector.h>
#include<headers/entity.h>

class window
{
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 800; 
    const int multiplier = 3;
public:
    void CreateWindow(const char* title);
    int  GetRefreshRate();
    void Display();
    void Clear();
    void Clean();
    SDL_Texture* Load(const char* path);
    void Render(entity& p_entity);
    void Render(SDL_Texture* tex, Vector p_pos);

};