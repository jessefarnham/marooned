/*
 * GameItem.h
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#ifndef SRC_GAMEITEM_H_
#define SRC_GAMEITEM_H_
#include <SDL2/SDL.h>
#include <string>

class GameItem {
public:
	GameItem();
	virtual std::string getTextureName() = 0;
	virtual bool getStandable() = 0;
	virtual ~GameItem();
};

#endif /* SRC_GAMEITEM_H_ */
