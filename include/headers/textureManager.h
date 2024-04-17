#pragma once

#include<headers/window.h>

class TextureManager
{
private:
    Window* window;
public:
    TextureManager() = default;
    TextureManager(Window &p_window);
    SDL_Texture* titleTexture = NULL;
    SDL_Texture* modeSeclectionTexture = NULL;
    SDL_Texture* classicModeTexture = NULL;
    SDL_Texture* hellModeTexture = NULL;
    SDL_Texture* pauseTexture = NULL;
    SDL_Texture* startTexture = NULL;
    SDL_Texture* playTexture = NULL;
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* gameOverTexture = NULL;
    SDL_Texture* spaceTexture[2] = {NULL, NULL};

    SDL_Texture* thanksIMG = NULL;
    SDL_Texture* cloud_bgTexture = NULL;

    SDL_Texture* musicPlayerPanelTexture = NULL;
    SDL_Texture* scorePanelTexture = NULL;
    SDL_Texture* flashTexture = NULL;
    
    SDL_Texture* groundTexture = NULL;
    SDL_Texture* OK_ButtonTexture = NULL;
    SDL_Texture* pipesTexture[2] = {NULL, NULL};
    SDL_Texture* medalTexture[3] = {NULL, NULL, NULL};

    SDL_Texture* musicPlayerTexture = NULL;
    SDL_Texture* musicPlayerPlayTexture = NULL;
    SDL_Texture* musicPlayerMuteTexture = NULL;
    SDL_Texture* shopTexture = NULL;

    SDL_Texture* forwardTexture = NULL;
    SDL_Texture* backwardTexture = NULL;

    SDL_Texture* shopPanel;
    SDL_Texture* pauseMusicTexture = NULL;
    SDL_Texture* resumeMusicTexture = NULL;

    SDL_Texture* totalCoinTexture = NULL;
    SDL_Texture* blank = NULL;
    SDL_Texture* select = NULL;
    SDL_Texture* handle = NULL;
    SDL_Texture* bar = NULL;
    SDL_Texture* nextChar = NULL;
    SDL_Texture* previousChar = NULL;
    SDL_Texture* CoinTextures[5] = {NULL, NULL, NULL, NULL, NULL};
    
    std::vector<SDL_Texture*> kittenIdleFrame;
    std::vector<SDL_Texture*> kittenJumpFrame;
    std::vector<SDL_Texture*> kittenFallFrame;
    
    void LoadTexture();
    void Render(int &currGameState, int &currScore, Uint32 &deadTime);
};
