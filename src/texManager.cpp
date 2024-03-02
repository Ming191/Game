#include<headers/texManager.h>


SDL_Texture* texManager::Load(const char* path, SDL_Renderer* gRenderer)
{   
    SDL_Texture* tmpTex;
    SDL_Surface* tmpSurface;
    tmpSurface = IMG_Load(path);
    SDL_SetColorKey( tmpSurface, SDL_TRUE, SDL_MapRGB( tmpSurface->format, 0x00, 0xFF, 0xFF ) );


    tmpTex = SDL_CreateTextureFromSurface(gRenderer,tmpSurface);
    return tmpTex;
}