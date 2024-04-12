#include<headers/Coin.h>

Coin::Coin(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

void Coin::Update()
{
    SetPos(Vector(GetPos().GetX(), GetPos().GetY() - 10.f));
}

