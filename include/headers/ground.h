#pragma once

#include<headers/entity.h>

const float groundScrollSpeed = 0.4f;

class ground : public entity
{
private:

public:
    ground() = default;
    ground(Vector p_pos, SDL_Texture* p_tex);
    void update();
};

