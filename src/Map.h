/*
 * Map.h
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "GameItem.h"
#include <vector>
#include <utility>
#include <memory>
#include "TextureLoader.h"


class Map {
public:
	Map(int size);
	virtual ~Map();
	void createEmpty();
	bool placePlayer(int r, int c);
	void render(TextureLoader&);
	std::pair<int, int> playerLoc;

private:
	std::vector<std::vector<std::unique_ptr<GameItem>>> state;
	int size;
};

#endif /* SRC_MAP_H_ */
