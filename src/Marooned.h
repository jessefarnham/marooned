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

	const std::string CONFIG_FILE = "config.txt";
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int MAP_SIZE;
	int VISIBLE_MAP_SIZE;
	int FONT_SIZE;
	int MESSAGE_QUEUE_SIZE;
	int TILE_SIZE;
	std::string SAVE_FILE;
	double FRAC_ARTIFACT;
	double FRAC_IMPASSABLE;
	double MAX_BASE_CARRY;

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* gFont = NULL;
	std::unique_ptr<Map> map;
	std::unique_ptr<MessageQueue> mq;

	void save();
	void load();
	void initConfig();
};

#endif /* MAROONED_H_ */
