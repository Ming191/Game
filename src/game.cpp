#include<headers/game.h>

game::game() {
	gWindow = NULL;
	gRenderer = NULL;

}

bool game::initGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Flappy Doge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				playerTex = texManager::Load("res/image/StyleBird1/Bird1-1.png", gRenderer);
				bgTex = texManager::Load("res/image/background/Background2.png", gRenderer);

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}
	isRunning = true;
	return success;
}

void game::clean()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);

    IMG_Quit();
    SDL_Quit();
	cout << "Game cleaned!" << endl;
}

void game::render()
{
    SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer,bgTex, NULL, NULL);
	SDL_RenderCopy(gRenderer,playerTex,&src, &dst);
    SDL_RenderPresent(gRenderer);
}

void game::handleEvents()
{	
	SDL_PollEvent(&evnt);

	switch (evnt.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
		cout << evnt.motion.x << " " << evnt.motion.y << endl;
		break;
	case SDL_MOUSEBUTTONDOWN:
		cout << "Mouse pressed!" << endl;
		break;
	default:
		break;
	}

	// if(evnt.type == SDL_QUIT) {
	// 	isRunning = false;
	// }
	// if(evnt.type == SDL_MOUSEBUTTONDOWN) {
	// 	cout << "PRESSED!" << endl;
	// }
	// if(evnt.type == SDL_MOUSEMOTION) {
	// 	cout << evnt.motion.x << " " << evnt.motion.y <<endl;
	// }


}

void game::update()
{
	src.h = 16;
	src.w = 16;
	src.x = src.y = 0;

	dst.h = 16;
	dst.w = 16;
	dst.y = 10;
	dst.x = 10;
}