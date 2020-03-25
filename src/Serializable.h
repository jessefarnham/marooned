/*
 * Serializable.h
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <fstream>

class Serializable {
public:
	Serializable();
	virtual void saveState(std::ofstream file) = 0;
	virtual void loadState(std::ifstream file) = 0;
	virtual ~Serializable();
};

#endif /* SERIALIZABLE_H_ */
