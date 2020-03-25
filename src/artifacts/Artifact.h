/*
 * Artifact.h
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#ifndef ARTIFACT_H_
#define ARTIFACT_H_

#include "../GameItem.h"

class Artifact: public GameItem {
public:
	Artifact();
	virtual std::string getTextureName();
	virtual bool getStandable();
	virtual double getWeight() = 0;
	virtual std::string getDescription();
	virtual int getDrawPriority();
	virtual ~Artifact();
};

#endif /* ARTIFACT_H_ */
