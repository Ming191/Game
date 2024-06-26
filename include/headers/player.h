#pragma once

#include<textureManager.h>
#include<sfx.h>
#include<math.h>

class Player: public Entity
{
private:
    Vector gravity;
    Vector velocity;
    float angle = 0.0f;
    SoundEffect* SFX;
    TextureManager* TManager;
public:
    std::vector<SDL_Texture*> playerIdleFrame;
    std::vector<SDL_Texture*> playerJumpFrame;
    std::vector<SDL_Texture*> playerFallFrame;

    float numToSin = 0.0f;
    bool canRolate = false;
    bool inFly = false;
    Player() = default;
    ~Player()= default;
    Player(Vector p_pos, SDL_Texture* p_texture, SoundEffect& p_SFX, TextureManager& p_tm);
    void MoveLeft();
    void Update();
    void Fly();
    float GetAngle();
    void SetAngle(float p_angle);
    void Pending(float maxRadius);
    void Reset();
    void SetPosMiddle();
    void NextChar();
    void PreviousChar();
    void ClearTexture();
    void SwitchCharacter();
};
