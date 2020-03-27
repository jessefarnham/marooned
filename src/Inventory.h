/*
 * Inventory.h
 *
 *  Created on: Mar 27, 2020
 *      Author: jesse
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <vector>
#include <memory>
#include <fstream>
#include "Serializable.h"
#include "artifacts/Artifact.h"

class Inventory : public Serializable {
public:
	Inventory();
	virtual ~Inventory();
	double getWeightIfAdd(Artifact&);
	double add(std::unique_ptr<Artifact>);
	std::unique_ptr<Artifact> drop(int i);
	double getWeight();
	void saveState(std::ofstream&);
	void loadState(std::ifstream&);
private:
	std::vector<std::unique_ptr<Artifact>> items;
	double weight;
	void clear();
};

#endif /* INVENTORY_H_ */
