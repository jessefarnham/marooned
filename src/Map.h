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
#include "MessageQueue.h"
#include "Player.h"


class Map : public Serializable {
public:
	Map(int size, int visibleSize, int tileSize, double baseMaxCarry);
	virtual ~Map();
	void createEmpty();
	void createRandom(double fracImpassable, double fracArtifact);
	bool placePlayer(int r, int c);
	bool movePlayerLeft();
	bool movePlayerRight();
	bool movePlayerUp();
	bool movePlayerDown();
	void render(TextureLoader&);
	void saveState(std::ofstream& file);
	void loadState(std::ifstream& file);
	void examine(MessageQueue& mq);
	std::pair<int, int> playerLoc;

private:
	bool isInBounds(std::pair<int, int>);
	bool tryMovePlayer(std::pair<int, int>);
	bool isStandable(int r, int c);
	void placeArtifacts(double fracArtifact);
	void createRandomTerrain(double fracImpassable);
	GameItem& getHighestPriorityItem(int r, int c);
	std::vector<std::vector<std::vector<std::unique_ptr<GameItem>>>> state;
	Player player;
	int size;
	int visibleSize;
	int tileSize;
	double fracImpassable;
};

#endif /* SRC_MAP_H_ */
