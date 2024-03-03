#pragma once

#include<headers/texManager.h>

class entity
{
private:
    SDL_Rect src, dst;
    SDL_Texture* tex;
public:
    entity(/* args */);

    void setSRC(int x, int y, int w, int h);
    void setDST(int x, int y, int w, int h);
    SDL_Texture* getTex();
    SDL_Rect getSRC();
    SDL_Rect getDST();

    void createTex(const char* path, SDL_Renderer* ren);
    void Render(SDL_Renderer* gRenderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dst);

};

