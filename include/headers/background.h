#pragma once

#include<defs.h>
#include<headers/window.h>

class Background : public Entity
{
private:
    
public:
    Background() = default;
    Background(Vector p_pos, SDL_Texture* p_tex,float p_scrollSpeed);
    void Update();
    float scrollSpeed;
    
};

class ParallaxBG
{
private:
    std::vector<Background> layer0;
    std::vector<Background> layer1;
    std::vector<Background> layer2;
    std::vector<Background> layer3;
    std::vector<Background> layer4;
    bool ShowText = 0;
    Window renderWindow;
public:
    ParallaxBG() = default;
    ParallaxBG(Window& p_Window);
    void Render();
    void Update();
    bool isShowText() {return ShowText;};
    void SwitchState(){ShowText = !ShowText;};
    void Reset();
};

class Foreground
{
private:
    std::vector<Background> foreGround;
public:
    void Init(Window &window);
    void Update();
    void Render(Window &window);
};