#pragma once
#include<button.h>
#include<PipeLink.h>

class Timer
{
private:
    float _cTime = 0.0f;
    float _timeStep = 0.1f;
    int playerIdleFrameIndex = 0;
    int playerJumpFrameIndex = 0;
    int playerFallFrameIndex = 0;
    int coinFrameIndex = 0;
    float spaceFrameIndex = 0;
    float scoreAccumulator = 0.f;
    

public:
    bool scored = false;
    Uint32 deadTime = 0;
    
    void Update(Player &p);
    void UpdateDeadTime();
    void IsScored();
    void Reset();
    void PlayerFrameUpdate(Player &p);
    void SpaceFrameUpdate(ButtonManager& BMAnager, TextureManager& TextureManager);
    void CoinFrameUpdate(PipeLinked &p, TextureManager &TManager);
};

