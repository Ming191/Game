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
    TextureManager* TManager;
public:
    GroundLinked() = default;
    GroundLinked(TextureManager &p_TM);
    void Init();
    void Update();
    void Render(Window &p);
    void CheckCollision(Entity &p, int &currGameState, SoundEffect &SFX);
};