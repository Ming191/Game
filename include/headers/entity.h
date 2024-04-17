#pragma once

#include<headers/defs.h>
#include<headers/sfx.h>
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
    void SetTex(SDL_Texture* p_tex);
    void UpdateCurrFrame(SDL_Texture *p_tex);
    SDL_Rect GetCurrFrame();
};

