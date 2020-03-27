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

void Bolts::saveState(std::ofstream& out) {
	out << "Bolts\n";
	out << n << "\n";
	out << weightPer << "\n";
}

void Bolts::loadState(std::ifstream& in) {
	std::string line;
	int n;
	double weightPer;
	in >> n;
	in >> weightPer;
	getline(in, line); //trailing newline
	this->n = n;
	this->weightPer = weightPer;
}

Bolts::~Bolts() {
	// TODO Auto-generated destructor stub
}

