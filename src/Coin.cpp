#include<headers/Coin.h>

Coin::Coin(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{
    randomDirection = ((rand() % 2) == 0) ? -1 : 1;
}

void Coin::Update()
{
    SetPos(Vector(GetPos().GetX(), GetPos().GetY() - 2.f*randomDirection));
}

void Coin::CheckHit(SoundEffect &SFX)
{
    if(isHit)
	{
		if(SDL_GetTicks() - hitTime < 20)
		{
			SFX.Play(COIN_HIT);
		}
		Update();
	}
}