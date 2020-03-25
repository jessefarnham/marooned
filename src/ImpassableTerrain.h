/*
 * ImpassableTerrain.h
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#ifndef IMPASSABLETERRAIN_H_
#define IMPASSABLETERRAIN_H_

#include "Terrain.h"

class ImpassableTerrain: public Terrain {
public:
	ImpassableTerrain();
	std::string getTextureName();
	virtual bool getStandable();
	virtual std::string getDescription();
	virtual ~ImpassableTerrain();
};

#endif /* IMPASSABLETERRAIN_H_ */
