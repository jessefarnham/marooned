/*
 * GameItem.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#include "GameItem.h"
#include "artifacts/Bolts.h"

GameItem::GameItem() {
	// TODO Auto-generated constructor stub

}

int GameItem::getDrawPriority(){
	return 0;
}

GameItem::~GameItem() {
	// TODO Auto-generated destructor stub
}

std::unique_ptr<GameItem> createGameItem(std::string itemName) {
	std::unique_ptr<GameItem> gameItem;
	if (itemName == "Bolts") {
		gameItem = std::make_unique<Bolts>(0, 0);
	}
	else {
		throw "Unknown item name" + itemName;
	}
	return gameItem;
}
