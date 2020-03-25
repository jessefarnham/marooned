/*
 * Marooned.cpp
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#include "Marooned.h"
#include "Map.h"
#include "MessageQueue.h"

Marooned::Marooned(unsigned int randseed) {
	this->randseed = randseed;
	srand(randseed);
}

bool Marooned::init()
{
	//Initialization flag
		bool success = true;

		//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			{
				printf( "Warning: Linear texture filtering not enabled!" );
			}

			//Create window
			gWindow = SDL_CreateWindow( "Marooned", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if( gWindow == NULL )
			{
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Create vsynced renderer for window
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
				if( gRenderer == NULL )
				{
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) )
					{
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
						success = false;
					}

					 //Initialize SDL_ttf
					if( TTF_Init() == -1 )
					{
						printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
						success = false;
					}
					else {
						gFont = TTF_OpenFont("/home/jesse/dev/marooned/fonts/UbuntuMono-BI.ttf", FONT_SIZE);
						if (gFont == NULL) {
							printf("Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
							success = false;
						}
					}
				}
			}
		}

		return success;
}

void Marooned::close()
{
	//Free loaded image

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Marooned::mainLoop(){
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	Map map(MAP_SIZE, VISIBLE_MAP_SIZE);
	map.createRandom(FRAC_IMPASSABLE);
	int tryPlayerR = MAP_SIZE / 2;
	int tryPlayerC = MAP_SIZE / 2;
	while (!map.placePlayer(tryPlayerR, tryPlayerC)){
		tryPlayerR++;
		tryPlayerC++;
		if (tryPlayerR > MAP_SIZE || tryPlayerC > MAP_SIZE) {
			throw "Could not find an open spot to place the player";
		}
	}
	MessageQueue mq(MESSAGE_QUEUE_SIZE);
	TextureLoader textureLoader(gRenderer, gFont);

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
				case SDLK_UP:
					map.movePlayerUp();
					mq.postMessage("You went up!");
					break;
				case SDLK_DOWN:
					map.movePlayerDown();
					mq.postMessage("You went down!");
					break;
				case SDLK_LEFT:
					map.movePlayerLeft();
					break;
				case SDLK_RIGHT:
					map.movePlayerRight();
					break;
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( gRenderer );

		//Top viewport
		SDL_Rect topViewport;
		topViewport.x = 0;
		topViewport.y = 0;
		topViewport.w = SCREEN_WIDTH;
		topViewport.h = SCREEN_HEIGHT * 3 / 4;
		SDL_RenderSetViewport( gRenderer, &topViewport );

		//Render map
		map.render(textureLoader);

		//Bottom viewport
		SDL_Rect bottomViewport;
		bottomViewport.x = 0;
		bottomViewport.y = SCREEN_HEIGHT * 3 / 4;
		bottomViewport.w = SCREEN_WIDTH;
		bottomViewport.h = SCREEN_HEIGHT / 4;
		SDL_RenderSetViewport( gRenderer, &bottomViewport );

		mq.render(textureLoader);


		//Update screen
		SDL_RenderPresent( gRenderer );
	}
}


Marooned::~Marooned() {
	// TODO Auto-generated destructor stub
}

