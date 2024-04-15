#include<headers/ground.h>

Ground::Ground(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

void Ground::Update()
{
	SetPos(Vector(GetPos().GetX() - groundScrollSpeed, SCREEN_HEIGHT/MULTIPLIER-GetCurrFrame().h));

	if (GetPos().GetX() <= -GetCurrFrame().w)
	{
		SetPos(Vector(GetCurrFrame().w, GetPos().GetY()));
	}

}