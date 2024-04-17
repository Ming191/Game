#pragma once

#include <headers/entity.h>
#include<textureManager.h>

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
    void SetGravity(float p_g)
    {
        gravity.SetY(p_g);
    };
};
