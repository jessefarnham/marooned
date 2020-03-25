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

class Marooned {
public:
	Marooned(unsigned int randseed);
	bool init();
	void close();
	void mainLoop();
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

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* gFont = NULL;
};

#endif /* MAROONED_H_ */
