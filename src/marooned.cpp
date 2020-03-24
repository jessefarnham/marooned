//============================================================================
// Name        : marooned.cpp
// Author      : Jesse Farnham
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Map.h"
#include "TextureLoader.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int MAP_SIZE = 20;

const int FONT_SIZE = 12;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

bool init()
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
			gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

void close()
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

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		Map map(MAP_SIZE);
		map.createEmpty();
		map.placePlayer(MAP_SIZE / 2, MAP_SIZE / 2);
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
						break;
					case SDLK_DOWN:
						map.movePlayerDown();
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

			//Update screen
			SDL_RenderPresent( gRenderer );
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}
