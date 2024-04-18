#pragma once

#include<headers/entity.h>
#include<headers/commonFunc.h>
#include<textureManager.h>
#include<sfx.h>


const float groundScrollSpeed = 0.9f;

class Ground : public Entity
{
private:

public:
    Ground() = default;
    Ground(Vector p_pos, SDL_Texture* p_tex);
    void Update();
};


class GroundLinked
{
private:
    std::vector<Ground> base;
public:
    GroundLinked() = default;
    void Init(TextureManager &TManager);
    void Update();
    void Render(Window &p);
    void CheckCollision(Entity &p, SoundEffect &SFX);
};