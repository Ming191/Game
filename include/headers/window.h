#pragma once

#include<defs.h>
#include<headers/entity.h>

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
    void RenderScale(SDL_Texture* p_tex, Vector p_pos, int scale);
    void RenderScale(Entity &e, int scale);
    void RenderRotate(Entity &e, Vector p_pos, float p_angle);
    void RenderText(Vector p_pos, std::string text, std::string FontPath,int size, SDL_Color color, bool flag);
    SDL_Texture* Flash();
};

