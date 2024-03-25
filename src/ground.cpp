#include<headers/ground.h>

ground::ground(Vector p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex)
{}

void ground::update()
{
	setPos(Vector(getPos().GetX() - scrollSpeed, 210.0f));

	if (getPos().GetX() <= -groundBoundary)
	{
		setPos(Vector(154, 210));
	}

}