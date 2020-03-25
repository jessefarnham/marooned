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
#include "Serializable.h"


class Map : public Serializable {
public:
	Map(int size, int visibleSize, int tileSize);
	virtual ~Map();
	void createEmpty();
	void createRandom(double fracImpassable);
	bool placePlayer(int r, int c);
	bool movePlayerLeft();
	bool movePlayerRight();
	bool movePlayerUp();
	bool movePlayerDown();
	void render(TextureLoader&);
	void saveState(std::ofstream& file);
	void loadState(std::ifstream& file);
	std::pair<int, int> playerLoc;

private:
	bool isInBounds(std::pair<int, int>);
	bool tryMovePlayer(std::pair<int, int>);
	std::vector<std::vector<std::unique_ptr<GameItem>>> state;
	int size;
	int visibleSize;
	int tileSize;
};

#endif /* SRC_MAP_H_ */
