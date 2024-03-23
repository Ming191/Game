#pragma once

#include <headers/entity.h>

class player: public entity
{
private:
    
public:
    player() = default;
    player(Vector p_pos, SDL_Texture* p_texture);

};

