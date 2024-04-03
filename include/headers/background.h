#pragma once

#include<headers/entity.h>

const float BGscrollSpeed = 0.4f;

class background : public entity
{
private:
    
public:
    background() = default;
    background(Vector p_pos, SDL_Texture* p_tex);
    void Update();
};
