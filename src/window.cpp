#include<headers/window.h>
#include<iostream>

void window::CreateWindow(const char* title)
{
    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL) {
        std::cout << "Failed to create window!" << SDL_GetError() << std::endl;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

int window::GetRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(gWindow);
    SDL_DisplayMode displayMode;
    SDL_GetDisplayMode(displayIndex,0,&displayMode);

    return displayMode.refresh_rate;
}

void window::Display()
{
    SDL_RenderPresent(gRenderer);
}

void window::Clear()
{
    SDL_RenderClear(gRenderer);
}

void window::Clean()
{
    SDL_DestroyWindow(gWindow);
}

SDL_Texture* window::Load(const char* p_path)
{
        //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(p_path);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", p_path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", p_path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface);
    }

    return newTexture;
}

void window::Render(entity& p_entity)
{
	SDL_Rect src = 
    {
        p_entity.getCFrame().x,
        p_entity.getCFrame().y,
        p_entity.getCFrame().w,
        p_entity.getCFrame().h,
    };

	SDL_Rect dst= 
    {
        (int)p_entity.getPos().GetX() * multiplier,
        (int)p_entity.getPos().GetY() * multiplier,
        (int)p_entity.getCFrame().w * multiplier,
        (int)p_entity.getCFrame().h * multiplier,
    };

	SDL_RenderCopy(gRenderer, p_entity.getTex(), &src, &dst);
}