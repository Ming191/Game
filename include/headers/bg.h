#pragma once

#include<headers/entity.h>
class bg: public entity
{
private:
    /* data */
public:
    void Render(SDL_Renderer* ren, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest);
	void Render(SDL_Renderer* ren, SDL_Texture* Tex);

};