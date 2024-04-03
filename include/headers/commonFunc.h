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
    inline bool isCollide(Entity a, Entity b)
    {
        float left_a   = a.GetPos().GetX();
        float right_a  = a.GetPos().GetX() + (float)a.GetCurrFrame().w;
        float top_a    = a.GetPos().GetY();
        float bottom_a = a.GetPos().GetY()+ (float)a.GetCurrFrame().h;

        float left_b   = b.GetPos().GetX();
        float right_b  = b.GetPos().GetX() + (float)b.GetCurrFrame().w;
        float top_b    = b.GetPos().GetY();
        float bottom_b = b.GetPos().GetY()+ (float)b.GetCurrFrame().h; 
        

        if (right_a >= left_b && left_a <= right_b && bottom_a >= top_b && top_a <= bottom_b)
        {
            return true; // Collision detected
        }
        return false;
    }

    inline bool isCollide(Vector a, Entity b)
    {
        float a_x = a.GetX();
        float a_y = a.GetY();

        float left_b   = b.GetPos().GetX();
        float right_b  = b.GetPos().GetX() + (float)b.GetCurrFrame().w;
        float top_b    = b.GetPos().GetY();
        float bottom_b = b.GetPos().GetY()+ (float)b.GetCurrFrame().h; 

        if(a_x >= left_b  && a_x <= right_b && a_y >= top_b && a_y <= bottom_b )
        {
            return true;
        }
        return false;
    }

    inline int getRandomValues(int p_min, int p_max)
    {
        return (rand() % (p_max - p_min + 1)) + p_min;
    }
} // namespace commonFunc
