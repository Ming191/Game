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

GroundLinked::GroundLinked(TextureManager &p_TM)
			: TManager(&p_TM)
{}

void GroundLinked::Init()
{
	base.emplace_back(Ground(Vector(0.f, 200.f), TManager->groundTexture));
	base.emplace_back(Ground(Vector(154.f, 200.f), TManager->groundTexture));
}

void GroundLinked::Update()
{
	for (int i = 0; i < 2; i++)
	{
		base[i].Update();
	}
}

void GroundLinked::Render(Window &window)
{
	for (int i = 0; i < 2; i++)
	{
		window.Render(base[i]);
	}
}

void GroundLinked::CheckCollision(Entity &p, int &currGameState, SoundEffect &SFX)
{
	for(int i = 0; i<2; i++)
	{
		if(commonFunc::isCollide(p,base[i])) 
		{
			currGameState = DIE;
			SFX.Play(PIPE_HIT);
		};
	}
}