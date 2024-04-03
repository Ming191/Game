#pragma once

#include <headers/entity.h>

class Player: public Entity
{
private:
    Vector gravity;
    Vector velocity;
    bool inFly = false;
public:
    Player() = default;
    Player(Vector p_pos, SDL_Texture* p_texture);
    void Update();
    void Fly();
};
