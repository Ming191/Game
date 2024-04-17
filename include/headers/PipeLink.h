#pragma once
#include<textureManager.h>
#include<pipe.h>
#include<Coin.h>

class PipeLink
{
private:
    std::vector<Pipe> pipeUp;
    std::vector<Pipe> pipeDown;
    std::vector<Coin> Coins;
public:
    void Init(TextureManager& TManager);
    void Render(Window &window);
    void Update(int &gameMode);
    void Reset(TextureManager& TManager);
    void RestartLoop();
    void CheckPlayerPass(SoundEffect& SFX, int &currScore, int &totalCoin, bool &scored,int &currGameState, Entity &p);
    void CoinAnimation(TextureManager &TManager, int &coinFrameIndex);
    void CheckCollision(Entity &p, SoundEffect &SFX, int &currGameState);
};

