/*
 * Bolts.h
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#ifndef ARTIFACTS_BOLTS_H_
#define ARTIFACTS_BOLTS_H_

#include "Artifact.h"

class Bolts: public Artifact {
public:
	Bolts(int n, double weightPer);
	virtual double getWeight();
	virtual std::string getDescription();
	virtual ~Bolts();

private:
	int n;
	double weightPer;
};

#endif /* ARTIFACTS_BOLTS_H_ */
