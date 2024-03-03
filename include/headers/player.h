#pragma once

#include <headers/entity.h>

class player: public entity
{
private:
    
public:
    void Render(SDL_Renderer* gRenderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dst);

};

