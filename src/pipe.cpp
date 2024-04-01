#include<headers/pipe.h>

pipe::pipe(Vector p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex)
{}

void pipe::update()
{
	setPos(Vector(getPos().GetX() - pipeScrollSpeed, getPos().GetY()));

	if (getPos().GetX() <= -pipeSpace)
	{
		setPos(Vector(240, getPos().GetY()));
        isCrossed = true;
	}

}