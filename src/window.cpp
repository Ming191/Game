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
