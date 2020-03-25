/*
 * Terrain.h
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "GameItem.h"

class Terrain: public GameItem {
public:
	Terrain();
	virtual void saveState(std::ofstream&);
	virtual void loadState(std::ifstream&);
	virtual ~Terrain();
};

#endif /* TERRAIN_H_ */
