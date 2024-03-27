#include<headers/background.h>

background::background(Vector p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex)
{}

void background::update()
{
	setPos(Vector(getPos().GetX() - BGscrollSpeed, 0.0f));

	if (getPos().GetX() <= -backgroundBoundary)
	{
		setPos(Vector(144, 0.0f));
	}

}