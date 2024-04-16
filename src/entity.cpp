#include<headers/entity.h>
#include "entity.h"

SDL_Texture* Entity::getTex()
{
    return tex;
}

Entity::Entity(Vector p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	cFrame.x = 0;
	cFrame.y = 0;
	SDL_QueryTexture(tex, NULL, NULL, &cFrame.w, &cFrame.h);
}

Vector &Entity::GetPos()
{
	return pos;
}

void Entity::SetPos(Vector p_pos)
{
	pos = p_pos;
}

SDL_Rect Entity::GetCurrFrame()
{
	return cFrame;
}

void Entity::SetTex(SDL_Texture* p_tex)
{
	tex = p_tex;
}

void Entity::UpdateCurrFrame()
{
	SDL_QueryTexture(tex, NULL, NULL, &cFrame.w, &cFrame.h);
}
