#pragma once

#include <headers/entity.h>
#include<math.h>

class Player: public Entity
{
private:
    Vector gravity;
    Vector velocity;
    
    float angle = 0.0f;
    float numToSin = 0.0f;

    SoundEffect* SFX;
public:
    bool inFly = false;
    Player() = default;
    Player(Vector p_pos, SDL_Texture* p_texture, SoundEffect& p_SFX);
    void Update();
    void Fly();
    float GetAngle();
    void SetAngle(float p_angle);
    void Pending(float maxRadius);
};
