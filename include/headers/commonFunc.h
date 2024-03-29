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
    inline bool isCollide(entity a, entity b)
    {
        float left_a   = a.getPos().GetX();
        float right_a  = a.getPos().GetX() + (float)a.getCFrame().w;
        float top_a    = a.getPos().GetY();
        float bottom_a = a.getPos().GetY()+ (float)a.getCFrame().h;

        float left_b   = b.getPos().GetX();
        float right_b  = b.getPos().GetX() + (float)b.getCFrame().w;
        float top_b    = b.getPos().GetY();
        float bottom_b = b.getPos().GetY()+ (float)b.getCFrame().h; 
        

        if((left_a >= left_b && left_a <= right_b) && (top_a >= top_b && top_a<=bottom_b))
        {
            return true;
        }
        return false;
    }

    inline bool isCollide(Vector a, entity b)
    {
        float a_x = a.GetX();
        float a_y = a.GetY();

        float left_b   = b.getPos().GetX();
        float right_b  = b.getPos().GetX() + (float)b.getCFrame().w;
        float top_b    = b.getPos().GetY();
        float bottom_b = b.getPos().GetY()+ (float)b.getCFrame().h; 

        if(a_x >= left_b  &&
           a_x <= right_b &&
           a_y >= top_b   &&
           a_y <= bottom_b )
        {
            return true;
        }
        return false;
    }
} // namespace commonFunc
