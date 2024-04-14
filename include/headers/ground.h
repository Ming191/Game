#pragma once

#include<headers/entity.h>

const float groundScrollSpeed = 0.9f;

class Ground : public Entity
{
private:

public:
    Ground() = default;
    Ground(Vector p_pos, SDL_Texture* p_tex);
    void Update();
};

