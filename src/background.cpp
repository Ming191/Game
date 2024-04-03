#include<headers/background.h>

background::background(Vector p_pos, SDL_Texture* p_tex)
	:entity(p_pos, p_tex)
{}

void background::Update()
{
	setPos(Vector(getPos().GetX() - BGscrollSpeed, SCREEN_HEIGHT/MULTIPLIER-getCFrame().h));

	if (getPos().GetX() <= -getCFrame().w)
	{
		setPos(Vector(getCFrame().w, SCREEN_HEIGHT/MULTIPLIER-getCFrame().h));
	}

}