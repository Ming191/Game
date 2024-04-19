#include<headers/player.h>

Player::Player(Vector p_pos, SDL_Texture* p_texture, SoundEffect& p_SFX, TextureManager& p_tm)
	:Entity(p_pos, p_texture), SFX(&p_SFX), TManager(&p_tm)
{
	gravity.SetX(0.0f);
	gravity.SetY(0.04f);

	playerIdleFrame = TManager->kitten[0];
	playerJumpFrame = TManager->kitten[1];
	playerFallFrame = TManager->kitten[2];
}

void Player::Update()
{
	if (GetPos().GetX() > 30)
	{
		MoveLeft();
	}
	
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

	if(GetPos().GetY() > 200 - GetCurrFrame().h)
	{
		SetPos(Vector(GetPos().GetX(),  200 - GetCurrFrame().h));
	}
	if(GetPos().GetY() < 0) SetPos(Vector(GetPos().GetX(), 0));

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
	SetPos(Vector(GetPos().GetX(), GetPos().GetY() - maxRadius*std::sin(numToSin)/2));
}

void Player::MoveLeft()
{
	if (GetPos().GetX() > 30)
		SetPos(Vector(GetPos().GetX() - 0.4f, GetPos().GetY()));
}

void Player::Reset()
{
	numToSin = 0.0f;
	SetPos(Vector(SCREEN_WIDTH/6 - GetCurrFrame().w/2.f,100.f));
}

void Player::SetPosMiddle()
{
	SetPos(Vector(SCREEN_WIDTH/6 - GetCurrFrame().w/2, SCREEN_HEIGHT/6 - GetCurrFrame().h/2));
}

void Player::NextChar()
{
	CharacterIndex++;
	if (CharacterIndex == TOTAL_CHAR)
	{
		CharacterIndex = 0;
	}
}

void Player::PreviousChar()
{
	CharacterIndex--;
	if (CharacterIndex < 0)
	{
		CharacterIndex = TOTAL_CHAR - 1;
	}
}

void Player::ClearTexture()
{		
	playerIdleFrame.clear();
	playerJumpFrame.clear();
	playerFallFrame.clear();
}

void Player::SwitchCharacter()
{
	ClearTexture();
	switch (CharacterIndex)
	{
	case CAT:	
		playerIdleFrame = TManager->kitten[0];
		playerJumpFrame = TManager->kitten[1];
		playerFallFrame = TManager->kitten[2];
		break;
	case BREAD:
		playerIdleFrame = TManager->bread[0];
		playerJumpFrame = TManager->bread[1];
		playerFallFrame = TManager->bread[2];	
		break;
	case HAMBURGER:
		playerIdleFrame = TManager->burger[0];
		playerJumpFrame = TManager->burger[1];
		playerFallFrame = TManager->burger[2];
		break;
	default:
		break;
	}
	UpdateCurrFrame(playerIdleFrame[0]);
	SetPosMiddle();
	numToSin = 0.0f;
}
