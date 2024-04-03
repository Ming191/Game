#pragma once

#include<headers/entity.h>

const float BGscrollSpeed = 0.4f;

class Background : public Entity
{
private:
    
public:
    Background() = default;
    Background(Vector p_pos, SDL_Texture* p_tex);
    void Update();
};
