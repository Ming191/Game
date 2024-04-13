#include<headers/game.h>
#include <cstdlib>
#include <ctime>   

game* Game = new game();


int main(int argc, char* argv[]) {
    srand((time(0)));
    Uint32 startTicks;
    Uint32 frameTicks;
    int currentTime = 0;
    int fps = 0;
    while (!Game->isQuit())
    {
        startTicks = SDL_GetTicks();

        Game->HandleEvents();
        Game->Update();
        Game->Render();

        // fps++;

		// if ((startTicks - currentTime) > 1000.0f)
		// {
		// 	currentTime = startTicks;
		// 	std::cout << fps << std::endl;
		// 	fps = 0;
		// }
        
        frameTicks = SDL_GetTicks() - startTicks;
	    if (frameTicks < 1000.f / Game->getRefreshRate())
		SDL_Delay(1000.f / Game->getRefreshRate() - frameTicks);
    }
    
    Game->Clean();
    return 0;
}