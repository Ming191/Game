#include<headers/Pipe.h>

Pipe::Pipe(Vector p_pos, SDL_Texture* p_tex ,bool flag)
	:Entity(p_pos, p_tex), isUpper(flag)
{	
	verticalSpeed   = commonFunc::getRandomFloat(0.4,0.8);
	randomDirection = ((rand() % 2) == 0) ? -1 : 1;
}

void Pipe::UpdateHell()
{
    SetPos(Vector(GetPos().GetX() - pipeScrollSpeed, GetPos().GetY()));

    if(isUpper)
	{
		float newY = GetPos().GetY() + verticalSpeed * randomDirection;
		if (newY < PIPE_UP_MIN_Y || newY > PIPE_UP_MAX_Y) 
		{
			verticalSpeed = -verticalSpeed; 
			newY = GetPos().GetY() + verticalSpeed; 
		}
		SetPos(Vector(GetPos().GetX(), newY));
	}

    if (GetPos().GetX() <= -pipeSpace) {
        SetPos(Vector(240, GetPos().GetY()));
		randomDirection = ((rand() % 2) == 0) ? -1 : 1;
    	verticalSpeed   = commonFunc::getRandomFloat(0.4,0.8);
        isCrossed = true;
    }
}

void Pipe::UpdateClassic()
{
	SetPos(Vector(GetPos().GetX() - pipeScrollSpeed, GetPos().GetY()));

    if (GetPos().GetX() <= -pipeSpace) {
        SetPos(Vector(240, GetPos().GetY()));
        isCrossed = true;
    }
}