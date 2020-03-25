/*
 * ImpassableTerrain.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#include "ImpassableTerrain.h"

ImpassableTerrain::ImpassableTerrain() {
	// TODO Auto-generated constructor stub

}

bool ImpassableTerrain::getStandable(){
	return false;
}

std::string ImpassableTerrain::getTextureName(){
	return "impassableTerrain";
}

std::string ImpassableTerrain::getDescription(){
	return "Impassable terrain.";
}

ImpassableTerrain::~ImpassableTerrain() {
	// TODO Auto-generated destructor stub
}

