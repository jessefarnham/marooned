/*
 * Marooned.cpp
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 *
 *  The boilerplate for this largely comes from Lazy Foo' Productions' SDL tutorial, found at
 *  http://lazyfoo.net/tutorials/SDL/index.php
 */


#include <fstream>
#include <unordered_map>
#include "Marooned.h"
#include "Map.h"
#include "MessageQueue.h"

Marooned::Marooned(unsigned int randseed) {
	this->randseed = randseed;
	srand(randseed);
	initConfig();
}

bool Marooned::initSDL()
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

void Marooned::initGame(){
	map = std::make_unique<Map>(MAP_SIZE, VISIBLE_MAP_SIZE, TILE_SIZE);
	map->createRandom(fracImpassable, fracArtifact);
	int tryPlayerR = MAP_SIZE / 2;
	int tryPlayerC = MAP_SIZE / 2;
	while (!map->placePlayer(tryPlayerR, tryPlayerC)){
		tryPlayerR++;
		tryPlayerC++;
		if (tryPlayerR > MAP_SIZE || tryPlayerC > MAP_SIZE) {
			throw "Could not find an open spot to place the player";
		}
	}
	mq = std::make_unique<MessageQueue>(MESSAGE_QUEUE_SIZE);

}

void Marooned::initConfig(){
	std::ifstream in(CONFIG_FILE);
	std::string key;
	std::string value;
	std::unordered_map<std::string, std::string> configs;
	if (in.is_open()){
		while (!in.eof()){
			std::getline(in, key);
			std::getline(in, value);
			configs.insert(std::make_pair(key, value));
		}
		in.close();
		SCREEN_WIDTH = std::stoi(configs["SCREEN_WIDTH"]);
		SCREEN_HEIGHT = std::stoi(configs["SCREEN_HEIGHT"]);
		MAP_SIZE = std::stoi(configs["MAP_SIZE"]);
		VISIBLE_MAP_SIZE = std::stoi(configs["VISIBLE_MAP_SIZE"]);
		FONT_SIZE = std::stoi(configs["FONT_SIZE"]);
		MESSAGE_QUEUE_SIZE = std::stoi(configs["MESSAGE_QUEUE_SIZE"]);
		SAVE_FILE = configs["SAVE_FILE"];
		TILE_SIZE = std::stoi(configs["TILE_SIZE"]);

		fracImpassable = std::stod(configs["fracImpassable"]);
		fracArtifact = std::stod(configs["fracArtifact"]);
	}
	else {
		throw "Could not load config file " + CONFIG_FILE;
	}
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
	bool ctrlDown = false;

	//Event handler
	SDL_Event e;

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
					map->movePlayerUp();
					break;
				case SDLK_DOWN:
					map->movePlayerDown();
					break;
				case SDLK_LEFT:
					map->movePlayerLeft();
					break;
				case SDLK_RIGHT:
					map->movePlayerRight();
					break;
				case SDLK_LCTRL:
				case SDLK_RCTRL:
					ctrlDown = true;
					break;
				case SDLK_s:
					if (ctrlDown){
						save();
					}
					break;
				case SDLK_l:
					if (ctrlDown){
						load();
					}
					break;
				}
			}
			else if (e.type == SDL_KEYUP) {
				switch(e.key.keysym.sym) {
				case SDLK_LCTRL:
				case SDLK_RCTRL:
					ctrlDown = false;
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
		map->render(textureLoader);

		//Bottom viewport
		SDL_Rect bottomViewport;
		bottomViewport.x = 0;
		bottomViewport.y = SCREEN_HEIGHT * 3 / 4;
		bottomViewport.w = SCREEN_WIDTH;
		bottomViewport.h = SCREEN_HEIGHT / 4;
		SDL_RenderSetViewport( gRenderer, &bottomViewport );

		//Render message queue
		mq->render(textureLoader);


		//Update screen
		SDL_RenderPresent( gRenderer );
	}
}

void Marooned::saveState(std::ofstream& out) {
	out << "Marooned\n";
	out << randseed << "\n";
	out << fracImpassable << "\n";
	map->saveState(out);
	mq->saveState(out);
}

void Marooned::loadState(std::ifstream& in) {
	std::string line;
	int randseed;
	int fracImpassable;
	getline(in, line); //header
	in >> randseed;
	in >> fracImpassable;
	this->randseed = randseed;
	this->fracImpassable = fracImpassable;
	getline(in, line); //trailing newline
	map->loadState(in);
}

void Marooned::save() {
	std::ofstream out;
	out.open(SAVE_FILE, std::ios::trunc);
	saveState(out);
	out.close();
	mq->postMessage("Game saved.");
}

void Marooned::load() {
	std::ifstream in(SAVE_FILE);
	if (in.is_open()){
		loadState(in);
		mq->postMessage("Game loaded.");
	}
	else{
		mq->postError("Could not open save file " + SAVE_FILE);
	}
	in.close();
}


Marooned::~Marooned() {
	// TODO Auto-generated destructor stub
}

