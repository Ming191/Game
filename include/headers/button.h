#pragma once

#include<headers/entity.h>

class Button : public Entity
{
private:
    /* data */
public:
    Button() = default;
    Button(Vector p_pos, SDL_Texture* p_tex);
};

