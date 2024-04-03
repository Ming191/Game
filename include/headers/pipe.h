#pragma once

#include<headers/entity.h>
#include<algorithm>

const float pipeScrollSpeed = 0.5f;
const int pipeSpace = 40;


class Pipe : public entity
{
public:
    bool isCrossed = false;
    float randomDirection;
    float verticalSpeed = 0.2f;
    bool isUpper;


public:
    Pipe() = default;
    Pipe(Vector p_pos, SDL_Texture* p_tex, bool flag);
    void Update();
};