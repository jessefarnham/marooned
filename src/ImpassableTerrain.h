/*
 * ImpassableTerrain.h
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#ifndef IMPASSABLETERRAIN_H_
#define IMPASSABLETERRAIN_H_

#include "GameItem.h"

class ImpassableTerrain: public GameItem {
public:
	ImpassableTerrain();
	std::string getTextureName();
	virtual bool getStandable();
	virtual ~ImpassableTerrain();
};

#endif /* IMPASSABLETERRAIN_H_ */
