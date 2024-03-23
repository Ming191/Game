#include<headers/entity.h>

SDL_Texture* entity::getTex()
{
    return tex;
}

entity::entity(Vector p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	cFrame.x = 0;
	cFrame.y = 0;
	SDL_QueryTexture(tex, NULL, NULL, &cFrame.w, &cFrame.h);
}

Vector& entity::getPos()
{
	return pos;
}

void entity::setPos(Vector p_pos)
{
	pos = p_pos;
}

SDL_Rect entity::getCFrame()
{
	return cFrame;
}