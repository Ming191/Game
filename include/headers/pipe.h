#pragma once

#include<headers/entity.h>

const float pipeScrollSpeed = 0.5f;
const int pipeSpace = 40;

class pipe : public entity
{
public:
    bool isCrossed = false;
public:
    pipe() = default;
    pipe(Vector p_pos, SDL_Texture* p_tex);
    void update();
};