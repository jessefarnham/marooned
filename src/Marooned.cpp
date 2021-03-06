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
#include "ControlFSM.h"

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
	map = std::make_unique<Map>(MAP_SIZE, VISIBLE_MAP_SIZE, TILE_SIZE,
			MAX_BASE_CARRY);
	map->createRandom(FRAC_IMPASSABLE, FRAC_ARTIFACT);
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
		FRAC_ARTIFACT = std::stod(configs["FRAC_ARTIFACT"]);
		FRAC_IMPASSABLE = std::stod(configs["FRAC_IMPASSABLE"]);
		MAX_BASE_CARRY = std::stod(configs["MAX_BASE_CARRY"]);
		KEYMAP_FILE = configs["KEYMAP_FILE"];
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

	//Event handler
	SDL_Event e;

	TextureLoader textureLoader(gRenderer, gFont);

	//Set up FSM control events
	ControlFSM fsm(KEYMAP_FILE);
	fsm.registerAction(START_STATE, MOVE_UP,
			[this](ControlFSMEvent& e) {this->map->movePlayerUp();});
	fsm.registerAction(START_STATE, MOVE_LEFT,
			[this](ControlFSMEvent& e) {this->map->movePlayerLeft();});
	fsm.registerAction(START_STATE, MOVE_RIGHT,
			[this](ControlFSMEvent& e) {this->map->movePlayerRight();});
	fsm.registerAction(START_STATE, MOVE_DOWN,
			[this](ControlFSMEvent& e) {this->map->movePlayerDown();});
	fsm.registerAction(START_STATE, EXAMINE,
			[this](ControlFSMEvent& e) {this->map->examine(*(this->mq));});
	fsm.registerAction(CTRL_DOWN, SAVE,
			[this](ControlFSMEvent& e) {this->save();});
	fsm.registerAction(CTRL_DOWN, LOAD,
			[this](ControlFSMEvent& e) {this->load();});
	fsm.registerAction(PICK_UP, NUM_KEY_DOWN,
			[this](ControlFSMEvent& e) {this->map->tryPickUp(e.getNum());});
	fsm.registerAction(DROP, NUM_KEY_DOWN,
			[this](ControlFSMEvent& e) {this->map->drop(e.getNum());});
	fsm.registerAction(START_STATE, SHOW_INVENTORY,
			[this](ControlFSMEvent& e) {this->map->showInventory(*(this->mq));});

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
			else {
				fsm.processEvent(e);
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
	map->saveState(out);
	mq->saveState(out);
}

void Marooned::loadState(std::ifstream& in) {
	std::string line;
	int randseed;
	getline(in, line); //header
	in >> randseed;
	this->randseed = randseed;
	srand(randseed);
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

