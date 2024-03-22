#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class texManager
{
private:
    
public:
    static SDL_Texture* Load(const char* path, SDL_Renderer* gRenderer);
};



