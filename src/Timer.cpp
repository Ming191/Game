
#include<headers/Timer.h>

void Timer::Update(Player &p)
{
    if (_cTime >= _timeStep)
	{
		_cTime = 0.0f;
		playerIdleFrameIndex +=1;
		playerJumpFrameIndex +=1;
		playerFallFrameIndex +=1;
		coinFrameIndex += 1;
		spaceFrameIndex += 0.25f;
		if (playerIdleFrameIndex > p.playerIdleFrame.size()-1) playerIdleFrameIndex = 0;
		if (playerJumpFrameIndex > p.playerJumpFrame.size()-1) playerJumpFrameIndex = 0;
		if (playerFallFrameIndex > p.playerFallFrame.size()-1) playerFallFrameIndex = 0;
		if (coinFrameIndex > 4) coinFrameIndex = 0;
		if(spaceFrameIndex > 1) spaceFrameIndex = 0;
	}
	_cTime += 0.01f;
}

void Timer::UpdateDeadTime()
{
    if (deadTime == 0)
    {
        deadTime = SDL_GetTicks();
    }
}

void Timer::IsScored()
{
    if (scored)
	{
		scoreAccumulator += 0.02f;
		if (scoreAccumulator >= scoreStep)
		{
			scoreAccumulator = 0.f;
			scored = false;
		}
	}
}

void Timer::Reset()
{
    deadTime = 0;
}

void Timer::PlayerFrameUpdate(Player &p, int &currGameState)
{
    switch (currGameState)
	{
	case PLAY:
		if(p.inFly) p.SetTex(p.playerJumpFrame[playerJumpFrameIndex]);
		else p.SetTex(p.playerFallFrame[playerFallFrameIndex]);
		break;
	default:
		p.SetTex(p.playerIdleFrame[playerIdleFrameIndex]);
		break;
	}
}

void Timer::SpaceFrameUpdate(ButtonManager& BManager, TextureManager& TManager)
{
    BManager.SpaceIMG.SetTex(TManager.spaceTexture[(int)spaceFrameIndex]);
}

void Timer::CoinFrameUpdate(PipeLink& pipeLink, TextureManager &TManager)
{
    pipeLink.CoinAnimation(TManager, coinFrameIndex);
}