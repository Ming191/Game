#pragma once

#include<headers/entity.h>

const float BGscrollSpeed = 0.4f;
const float backgroundBoundary = 144*5; // = width of Background asset

class background : public entity
{
private:
    
public:
    background() = default;
    background(Vector p_pos, SDL_Texture* p_tex);
    void update();
};
