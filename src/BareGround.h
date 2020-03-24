/*
 * BareGround.h
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#ifndef SRC_BAREGROUND_H_
#define SRC_BAREGROUND_H_

#include "GameItem.h"
#include <string>

class BareGround : public GameItem {
public:
	BareGround();
	std::string getTextureName();
	virtual bool getStandable();
	virtual ~BareGround();
};

#endif /* SRC_BAREGROUND_H_ */
