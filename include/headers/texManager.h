#pragma once

#include<headers/game.h>


class texManager
{
private:
    
public:
    int tWidth;
    int tHeight;
    static SDL_Texture* Load(const char* path, SDL_Renderer* gRenderer);
    static void free();    
};



