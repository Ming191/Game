#include<headers/PipeLink.h>

void PipeLink::Init(TextureManager& TManager)
{
    float pipeX = 240.f;
	for (int i = 1; i<=4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), TManager.pipesTexture[0], 1));
		float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), TManager.pipesTexture[1], 0));
		Coins.emplace_back(Coin(Vector(pipeX + 13 - 8, pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP/2 - 8), TManager.CoinTextures[0]));
		pipeX += 90;
	}
}

void PipeLink::Render(Window &window)
{
    for (int i = 0; i < 4; i++)
	{
		if(!(Coins[i].isHit && Coins[i].hitTime!= 0 && SDL_GetTicks() - Coins[i].hitTime > 600)) window.Render(Coins[i]);
	}
    for (int i = 0; i<4; i++)
	{
		window.Render(pipeUp[i]);
		window.Render(pipeDown[i]);
	}
}

void PipeLink::Update(int &gameMode)
{
    if (gameMode == CLASSIC_MODE)
    {
        	for (int i = 0; i<4; i++)
			{
				{
					pipeUp[i].UpdateClassic();
					pipeDown[i].UpdateClassic();
				}
				pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(),pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h +PIPE_GAP));
				Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, Coins[i].GetPos().GetY()));
			}
    }
    else
    {
        	for (int i = 0; i<4; i++)
			{
				{
					pipeUp[i].UpdateHell();
					pipeDown[i].UpdateHell();
				}
				pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(), pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h +PIPE_GAP));
				if(!Coins[i].isHit) Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h + PIPE_GAP/2 - 8));
				else Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, Coins[i].GetPos().GetY()));
			}
    }
}
void PipeLink::RestartLoop()
{
    for (int i = 0; i < 4; i++)
	{
		if (pipeUp[i].isCrossed)
		{
			float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
			pipeUp[i].SetPos(Vector(pipeUp[i].GetPos().GetX(), pipeUpY));
			pipeUp[i].isCrossed = false;
			float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;

			pipeDown[i].SetPos(Vector(pipeDown[i].GetPos().GetX(), pipeDownY));
			pipeDown[i].isCrossed = false;

			Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, pipeUpY + pipeUp[i].GetCurrFrame().h + PIPE_GAP/2 - 8));
			Coins[i].isHit = false;
			Coins[i].hitTime = 0;
		}
	}
}
int PipeLink::CheckCollision(Entity &p, SoundEffect &SFX)
{
    for (int i = 0; i < 4; i++)
    {
        if(commonFunc::isCollide(p, pipeUp[i]) || commonFunc::isCollide(p, pipeDown[i]))
		{
			SFX.Play(PIPE_HIT);
			return DIE;
		};
    }
	return PLAY;
}
void PipeLink::CheckPlayerPass(SoundEffect& SFX, int &currScore, int &totalCoin, bool &scored, Entity &p)
{
    for (int i = 0; i<4; i++)
	{
		if (commonFunc::CheckPass(p, pipeDown[i].GetPos().GetX() + (pipeDown[i].GetCurrFrame().w / 2.f), pipeDown[i].GetPos().GetY()) && !scored)
		{
			scored = true;
			if (scored)
			{
				if(Coins[i].hitTime == 0) Coins[i].hitTime = SDL_GetTicks();
				Coins[i].isHit = true;
			}
			currScore += 1;
			totalCoin += 1;
		}
		Coins[i].CheckHit(SFX);
	}   
}

void PipeLink::Reset(TextureManager& TManager)
{
    pipeUp.clear();
	pipeDown.clear();
	Coins.clear();
    float pipeX = 240.f;
	for (int i = 0; i<4; i++)
	{
		float pipeUpY = commonFunc::getRandomValues(PIPE_UP_MIN_Y, PIPE_UP_MAX_Y);
		pipeUp.emplace_back(Pipe(Vector(pipeX, pipeUpY), TManager.pipesTexture[0], 1));
		float pipeDownY = pipeUpY + pipeUp[0].GetCurrFrame().h + PIPE_GAP;
		pipeDown.emplace_back(Pipe(Vector(pipeX, pipeDownY), TManager.pipesTexture[1], 0));
		Coins[i].SetPos(Vector(pipeUp[i].GetPos().GetX() + 13 - 8, pipeUp[i].GetPos().GetY() + pipeUp[0].GetCurrFrame().h+PIPE_GAP/2 - 8));
		Coins[i].isHit = false;
		Coins[i].hitTime = 0;
		pipeX += 90;
	}
}

void PipeLink::CoinAnimation(TextureManager &TManager, int &coinFrameIndex)
{
    for (int i = 0; i < 4; i++)
	{
		Coins[i].SetTex(TManager.CoinTextures[coinFrameIndex]);
	}
}