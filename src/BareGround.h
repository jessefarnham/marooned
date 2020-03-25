/*
 * BareGround.h
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#ifndef SRC_BAREGROUND_H_
#define SRC_BAREGROUND_H_

#include <string>
#include "Terrain.h"


class BareGround : public Terrain {
public:
	BareGround();
	std::string getTextureName();
	virtual bool getStandable();
	virtual std::string getDescription();
	virtual ~BareGround();
};

#endif /* SRC_BAREGROUND_H_ */
