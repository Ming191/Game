#pragma once

#include<headers/entity.h>
#include<headers/commonFunc.h>
#include<algorithm>

const float pipeScrollSpeed = 0.9f;
const int pipeSpace = 120;

class Pipe : public Entity
{
public:
    int randomDirection;
    float verticalSpeed;
    bool isUpper;
public:
    bool isCrossed = false;
    Pipe() = default;
    Pipe(Vector p_pos, SDL_Texture* p_tex, bool flag);
    void UpdateHell();
    void UpdateClassic();
};
