#pragma once

#include<headers/entity.h>

class button : public entity
{
private:
    /* data */
public:
    button() = default;
    button(Vector p_pos, SDL_Texture* p_tex);
};

