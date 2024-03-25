#pragma once

#include <headers/entity.h>

class player: public entity
{
private:
    Vector gravity;
    Vector velocity;
    bool inFly = false;
public:
    player() = default;
    player(Vector p_pos, SDL_Texture* p_texture);
    void update();
    void fly();
};
