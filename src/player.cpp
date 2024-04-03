#include<headers/player.h>

player::player(Vector p_pos, SDL_Texture* p_texture)
	:entity(p_pos, p_texture)
{
	gravity.SetX(0.0f);
	gravity.SetY(0.04f);
}

void player::Update()
{
	setPos(Vector(30, getPos().GetY() + velocity.GetY()));
	velocity.AddTo(gravity);
	if (velocity.GetY() >= 1.0f)
	{
		inFly = false;
	}

	if (velocity.GetY() < 0.0f)
	{
		inFly = true;
	}
}

void player::Fly()
{
	velocity.SetY(-1.5f);
}