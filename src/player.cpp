#include<headers/player.h>

Player::Player(Vector p_pos, SDL_Texture* p_texture, SoundEffect& p_SFX)
	:Entity(p_pos, p_texture), SFX(&p_SFX)
{
	gravity.SetX(0.0f);
	gravity.SetY(0.04f);
}

void Player::Update()
{
	SetPos(Vector(GetPos().GetX(), GetPos().GetY() + velocity.GetY()));
	velocity.AddTo(gravity);
	if (velocity.GetY() >= 0.f)
	{
		inFly = false;
		angle +=2.f;
		if(angle > 450) angle = 450;
	}

	if (velocity.GetY() < 0.0f)
	{
		inFly = true;
		angle -=10.f;
		if(angle < 330) angle = 330;
	}
}

void Player::Fly()
{
	SFX->Play(JUMP);
	velocity.SetY(-1.25f);
}

float Player::GetAngle()
{
	return angle;
}

void Player::SetAngle(float p_angle)
{
	angle = p_angle;
}

void Player::Pending(float maxRadius)
{
	numToSin += 0.05f;
	velocity.SetY(maxRadius*std::sin(numToSin));
	SetPos(Vector(GetPos().GetX(), GetPos().GetY() - velocity.GetY()));
}