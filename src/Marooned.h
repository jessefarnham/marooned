/*
 * Marooned.h
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#ifndef MAROONED_H_
#define MAROONED_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <memory>
#include "Serializable.h"
#include "Map.h"
#include "MessageQueue.h"

class Marooned : public Serializable {
public:
	Marooned(unsigned int randseed);
	bool initSDL();
	void initGame();
	void close();
	void mainLoop();
	void saveState(std::ofstream& file);
	void loadState(std::ifstream& file);
	virtual ~Marooned();

private:
	unsigned int randseed;

	const int SCREEN_WIDTH = 480;
	const int SCREEN_HEIGHT = 640;
	const int MAP_SIZE = 100;
	const int VISIBLE_MAP_SIZE = 50;
	const int FONT_SIZE = 12;
	const double FRAC_IMPASSABLE = 0.2;
	const int MESSAGE_QUEUE_SIZE = 10;
	const std::string SAVE_FILE = "savegame.txt";

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* gFont = NULL;

	std::unique_ptr<Map> map;
	std::unique_ptr<MessageQueue> mq;

	void save();
	void load();
};

#endif /* MAROONED_H_ */
