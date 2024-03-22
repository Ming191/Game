#include<headers/player.h>

void player::Render(SDL_Renderer* gRenderer, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(gRenderer,getTex(), &src, &dst);
};