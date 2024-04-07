#include<headers/game.h>
#include <cstdlib>
#include <ctime>   

game* Game = new game();

float accumulator = 0.0f;
float cTime = commonFunc::hireTimeInSec();
float newTime = 0.0f;
float frameTime = 0.0f;
float alpha = 0.0f;
int startTicks;
int frameTicks;

void gameLoop()
{
        startTicks = SDL_GetTicks();

        newTime = commonFunc::hireTimeInSec();
        frameTime = newTime-cTime;
        cTime = newTime;
        accumulator += frameTime;

        while (accumulator >=timeStep)
        {
            Game->Run();
            accumulator -= timeStep;
        }
        // alpha = accumulator/timeStep; // not really necessary

        Game->Render();
        Game->Update();

        frameTicks = SDL_GetTicks() - startTicks;
	    if (frameTicks < 1000 / Game->getRefreshRate())
		SDL_Delay(1000 / Game->getRefreshRate() - frameTicks);
}

int main(int argc, char* argv[]) {
    srand((time(0)));
    while (!Game->isQuit())
    {
        gameLoop();
    }
    
    Game->Clean();
    return 0;
}