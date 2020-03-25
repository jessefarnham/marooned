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
#include <fstream>
#include "Serializable.h"
#include <memory>

class GameItem : Serializable {
public:
	GameItem();
	virtual std::string getTextureName() = 0;
	virtual bool getStandable() = 0;
	virtual int getDrawPriority();
	virtual std::string getDescription() = 0;
	virtual void saveState(std::ofstream&) = 0;
	virtual void loadState(std::ifstream&) = 0;
	virtual ~GameItem();
};

std::unique_ptr<GameItem> createGameItem(std::string itemName);

#endif /* SRC_GAMEITEM_H_ */
