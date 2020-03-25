/*
 * Bolts.cpp
 *
 *  Created on: Mar 25, 2020
 *      Author: jesse
 */

#include "Bolts.h"

Bolts::Bolts(int n, double weightPer) {
	this->n = n;
	this->weightPer = weightPer;
}

double Bolts::getWeight() {
	return n * weightPer;
}

std::string Bolts::getDescription(){
	return "A handful of alien bolts. They look quite similar to human-made ones.";
}

Bolts::~Bolts() {
	// TODO Auto-generated destructor stub
}

