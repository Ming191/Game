#include<headers/game.h>

game* Game = new game();

const float timeStep = 0.01f;
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
            Game->run();
            accumulator -= timeStep;
        }
        alpha = accumulator/timeStep; // not really necessary

        Game->render();

        Game->update();
        frameTicks = SDL_GetTicks() - startTicks;
	    if (frameTicks < 1000 / Game->getRefreshRate())
		SDL_Delay(1000 / Game->getRefreshRate() - frameTicks);
}

int main(int argc, char* argv[]) {    
    while (!Game->isQuit())
    {
        gameLoop();
    }
    
    Game->clean();
    return 0;
}