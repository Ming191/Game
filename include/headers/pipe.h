#pragma once

#include<headers/entity.h>
#include<algorithm>

const float pipeScrollSpeed = 0.8f;
const int pipeSpace = 120;

class Pipe : public Entity
{
public:
    bool isMove;
    bool isCrossed = false;
    float randomDirection;
    float verticalSpeed = 0.4f;
    bool isUpper;


public:
    Pipe() = default;
    Pipe(Vector p_pos, SDL_Texture* p_tex, bool flag);
    void Update();
};