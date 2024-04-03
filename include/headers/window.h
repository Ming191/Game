#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector.h>
#include<defs.h>
#include<headers/entity.h>

class Window
{
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    int gameState;

public:
    void CreateWindow(const char* title);
    int  GetRefreshRate();
    void Display();
    void Clear();
    void Clean();
    SDL_Texture* Load(const char* path);
    void Render(Entity& p_Entity);
    void Render(SDL_Texture* tex, Vector p_pos);

};