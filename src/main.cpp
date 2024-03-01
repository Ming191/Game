#include<headers/game.h>

game* Game = new game();

int main(int argc, char* argv[]) {
    Game->initGraphic();
    
    while (Game->running())
    {
        Game->render();
        Game->handleEvents();
    }
    
    Game->clean();
    return 0;
}