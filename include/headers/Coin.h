#pragma once

#include<headers/entity.h>

class Coin : public Entity
{
public:
    bool isHit = false;
    int randomDirection;
    Uint32 hitTime = 0;
public:
    Coin() = default;
    Coin(Vector p_pos, SDL_Texture* p_tex);
    void Update();
    void CheckHit(SoundEffect &SFX);
    
};

