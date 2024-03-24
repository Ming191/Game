#pragma once

#include<headers/entity.h>

const float groundVelocity = 0.4f;
const float groundBoundary = 154; // = width of Ground asset

class ground : public entity
{
private:

public:
    ground() = default;
    void init();
    ground(Vector p_pos, SDL_Texture* p_tex);
    void update();
};

