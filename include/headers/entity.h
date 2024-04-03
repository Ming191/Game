#pragma once

#include<SDL2/SDL.h>
#include<headers/defs.h>
#include<headers/vector.h>

class Entity
{
private:
    Vector pos;
    SDL_Rect cFrame;
    SDL_Texture* tex;
public:
    Entity() = default;
    Entity(Vector p_pos, SDL_Texture* p_tex);
    Vector& GetPos();
    void SetPos(Vector p_pos);
    SDL_Texture* getTex();
    SDL_Rect GetCurrFrame();
};

