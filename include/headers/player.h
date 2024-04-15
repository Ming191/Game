#pragma once

#include <headers/entity.h>
#include<math.h>

class Player: public Entity
{
private:
    Vector gravity;
    Vector velocity;
    bool inFly = false;
    float angle = 0.0f;
    float numToSin = 0.0f;

    SoundEffect* SFX;
public:
    Player() = default;
    Player(Vector p_pos, SDL_Texture* p_texture, SoundEffect& p_SFX);
    void Update();
    void Fly();
    float GetAngle();
    void SetAngle(float p_angle);
    void Pending(float maxRadius);
};
