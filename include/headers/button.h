#pragma once

#include<headers/entity.h>
#include<textureManager.h>

class Button : public Entity
{
private:
    /* data */
public:
    Button() = default;
    Button(Vector p_pos, SDL_Texture* p_tex);
};


class ButtonManager
{
private:
    TextureManager* TManager;
public:
    ButtonManager() = default;
    ButtonManager(TextureManager& p_tm);
    Button OK_Button;
    Button startButton;
    Button modeSelectionButton;
    Button classicModeButton;
    Button hellModeButton;
    Button pauseButton;
    Button playButton;
    Button menuButton;
    Button musicPlayerButton;
    Button musicPlayerPlayButton;
    Button sfxPlayerButton;
    Button shopButton;
    Button handleButton1;
    Button handleButton2;
    Button bar1;
    Button bar2;
    Button nextChar;
    Button previousChar;
    Button selectButton;
    Button SpaceIMG;
    Button forwardButton;
    Button backwardButton;
    Button PauseAndResumeMusic;


    void LoadButton();
};