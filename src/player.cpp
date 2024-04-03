#include<headers/player.h>

Player::Player(Vector p_pos, SDL_Texture* p_texture)
	:Entity(p_pos, p_texture)
{
	gravity.SetX(0.0f);
	gravity.SetY(0.04f);
}

void Player::Update()
{
	SetPos(Vector(30, GetPos().GetY() + velocity.GetY()));
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

void Player::Fly()
{
	velocity.SetY(-1.25f);
}