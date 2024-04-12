#pragma once

#include<headers/entity.h>

class Coin : public Entity
{
public:
    bool isHit = false;
public:
    Coin() = default;
    Coin(Vector p_pos, SDL_Texture* p_tex);
    void Update();
    
};
