#include<iostream>
#include<SDL2/SDL.h>

namespace commonFunc
{
    inline float hireTimeInSec()
    {
        float t = SDL_GetTicks();
        t *= 0.001;
        return t;
    }
} // namespace commonFunc
