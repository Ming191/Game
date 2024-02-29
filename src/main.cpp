#include "headers/game.h"

game *Mygame = nullptr;

int main(int argc, char* args[])
{
	Mygame = new game();

	Mygame->init("FlappyBird by Ming");

	while (Mygame->running())
	{
		Mygame->handleEvent();
		Mygame->update();
		Mygame->render();
	}

	Mygame->clean();
	return 0;
}