#include<headers/bg.h>

void bg::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTex(), NULL, NULL);
}
