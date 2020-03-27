/*
 * Player.h
 *
 *  Created on: Mar 27, 2020
 *      Author: jesse
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <memory>
#include <fstream>
#include "artifacts/Artifact.h"
#include "Inventory.h"
#include "Serializable.h"

class Player : public Serializable {
public:
	Player(double baseMaxCarry);
	virtual ~Player();
	int getHealth();
	int getFoodStatus();
	int getWaterStatus();
	bool pickUp(std::unique_ptr<Artifact>);
	std::unique_ptr<Artifact> drop(int itemIndex);
	void saveState(std::ofstream&);
	void loadState(std::ifstream&);
private:
	int health;
	int food;
	int water;
	double baseMaxCarry;
	Inventory inventory;
	double getMaxCarryWeight();
};

#endif /* PLAYER_H_ */
