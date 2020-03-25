/*
 * Artifact.cpp
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#include "Artifact.h"

Artifact::Artifact() {
	// TODO Auto-generated constructor stub

}

std::string Artifact::getTextureName(){
	return "artifact";
}

bool Artifact::getStandable(){
	return true;
}

int Artifact::getDrawPriority(){
	return 1; //artifacts always draw with higher priority than terrain
}

Artifact::~Artifact() {
	// TODO Auto-generated destructor stub
}

