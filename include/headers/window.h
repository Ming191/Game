#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector.h>
#include<defs.h>
#include<headers/entity.h>
#include<string>

class Window
{
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    int currGameState;

public:
    void CreateWindow(const char* title);
    int  GetRefreshRate();
    void Display();
    void Clear();
    void Clean();
    SDL_Texture* Load(const char* path);
    void Render(Entity& p_Entity);
    void Render(SDL_Texture* p_tex, Vector p_pos);
    void RenderRotate(SDL_Texture* p_tex, Vector p_pos, float p_angle);
    void RenderText(Vector p_pos, std::string text, TTF_Font* gFont, SDL_Color color);
};