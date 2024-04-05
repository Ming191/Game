#include<headers/window.h>
#include<iostream>

void Window::CreateWindow(const char* title)
{
    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL) {
        std::cout << "Failed to create Window!" << SDL_GetError() << std::endl;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

int Window::GetRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(gWindow);
    SDL_DisplayMode displayMode;
    SDL_GetDisplayMode(displayIndex,0,&displayMode);

    return displayMode.refresh_rate;
}

void Window::Display()
{
    SDL_RenderPresent(gRenderer);
}

void Window::Clear()
{
    SDL_RenderClear(gRenderer);
}

void Window::Clean()
{
    SDL_DestroyWindow(gWindow);
}

SDL_Texture* Window::Load(const char* p_path)
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

void Window::Render(Entity& p_Entity)
{
	SDL_Rect src = 
    {
        p_Entity.GetCurrFrame().x,
        p_Entity.GetCurrFrame().y,
        p_Entity.GetCurrFrame().w,
        p_Entity.GetCurrFrame().h,
    };

	SDL_Rect dst= 
    {
        (int)p_Entity.GetPos().GetX() * MULTIPLIER,
        (int)p_Entity.GetPos().GetY() * MULTIPLIER,
        (int)p_Entity.GetCurrFrame().w * MULTIPLIER,
        (int)p_Entity.GetCurrFrame().h * MULTIPLIER,
    };

	SDL_RenderCopy(gRenderer, p_Entity.getTex(), &src, &dst);
}

void Window::Render(SDL_Texture* p_tex, Vector p_pos)
{
	SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(p_tex, NULL,NULL, &src.w, &src.h);

	SDL_Rect dst= 
    {
        (int)p_pos.GetX() * MULTIPLIER,
        (int)p_pos.GetY() * MULTIPLIER,
        (int)src.w * MULTIPLIER,
        (int)src.h * MULTIPLIER
    };

	SDL_RenderCopy(gRenderer, p_tex , &src, &dst);
}

void Window::RenderRotate(SDL_Texture* p_tex, Vector p_pos, float p_angle)
{
    	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = (int)p_pos.GetX() * MULTIPLIER;
	dst.y = (int)p_pos.GetY() * MULTIPLIER;
	dst.w = src.w * MULTIPLIER;
	dst.h = src.h * MULTIPLIER;

	SDL_RenderCopyEx(gRenderer, p_tex, &src, &dst, p_angle, NULL, SDL_FLIP_NONE);
}
