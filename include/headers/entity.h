#pragma once

#include<SDL2/SDL.h>
#include<headers/defs.h>
#include<headers/vector.h>

class entity
{
private:
    Vector pos;
    SDL_Rect cFrame;
    SDL_Texture* tex;
public:
    entity() = default;
    entity(Vector p_pos, SDL_Texture* p_tex);
    Vector& getPos();
    void setPos(Vector p_pos);
    SDL_Texture* getTex();
    SDL_Rect getCFrame();
};

