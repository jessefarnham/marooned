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

virtual std::string Artifact::getTextureName(){
	return "artifact";
}

virtual bool Artifact::getStandable(){
	return true;
}

Artifact::~Artifact() {
	// TODO Auto-generated destructor stub
}

