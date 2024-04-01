#include<headers/ground.h>

ground::ground(Vector p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex)
{}

void ground::update()
{
	setPos(Vector(getPos().GetX() - groundScrollSpeed, SCREEN_HEIGHT/MULTIPLIER-getCFrame().h));

	if (getPos().GetX() <= - getCFrame().w)
	{
		setPos(Vector(getCFrame().w, SCREEN_HEIGHT/MULTIPLIER-getCFrame().h));
	}

}