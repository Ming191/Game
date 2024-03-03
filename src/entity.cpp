#include<headers/entity.h>

SDL_Rect entity::getSRC()
{
    return src;
}

SDL_Rect entity::getDST()
{
    return dst;
}

SDL_Texture* entity::getTex()
{
    return tex;
}

entity::entity()
{
    tex = NULL;
}

void entity::setSRC(int x, int y, int w, int h)
{
    src = {x,y,w,h};
}

void entity::setDST(int x, int y, int w, int h)
{
    dst = {x,y,w,h};
}

void entity::createTex(const char*path, SDL_Renderer* gRenderer)
{
    tex = texManager::Load(path,gRenderer);
}