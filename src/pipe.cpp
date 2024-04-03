#include<headers/Pipe.h>

Pipe::Pipe(Vector p_pos, SDL_Texture* p_tex ,bool flag)
	:entity(p_pos, p_tex), isUpper(flag)
{
	randomDirection = ((rand() % 2) == 0) ? -1 : 1;
	
}

void Pipe::Update()
{
    setPos(Vector(getPos().GetX() - pipeScrollSpeed, getPos().GetY()));

    if(isUpper)
	{
		float newY = getPos().GetY() + verticalSpeed * randomDirection;
		if (newY < PIPE_UP_MIN_Y || newY > PIPE_UP_MAX_Y) 
		{
			verticalSpeed = -verticalSpeed; 
			newY = getPos().GetY() + verticalSpeed; 
		}
		setPos(Vector(getPos().GetX(), newY));
	}
	else
	{
		float newY = getPos().GetY() + verticalSpeed * randomDirection;
		if (newY < PIPE_DOWN_MIN_Y || newY > PIPE_DOWN_MAX_Y) {
			verticalSpeed = -verticalSpeed; 
			newY = getPos().GetY() + verticalSpeed; 
		}
		setPos(Vector(getPos().GetX(), newY));
	}
	

    if (getPos().GetX() <= -pipeSpace) {
        setPos(Vector(240, getPos().GetY()));
        isCrossed = true;
    }
}