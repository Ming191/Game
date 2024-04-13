#include<headers/background.h>

Background::Background(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

void Background::Update()
{
	SetPos(Vector(GetPos().GetX() - BGscrollSpeed, SCREEN_HEIGHT/MULTIPLIER-GetCurrFrame().h));

	if (GetPos().GetX() <= -GetCurrFrame().w)
	{
		SetPos(Vector(GetCurrFrame().w, SCREEN_HEIGHT/MULTIPLIER-GetCurrFrame().h));
	}

}