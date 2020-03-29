/*
 * Inventory.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: jesse
 */

#include "Inventory.h"
#include "GameItem.h"
#include "artifacts/Artifact.h"


Inventory::Inventory() {
	weight = 0;
}

Inventory::~Inventory() {
	// TODO Auto-generated destructor stub
}

double Inventory::getWeightIfAdd(Artifact& item) {
	return weight + item.getWeight();
}

double Inventory::add(std::unique_ptr<Artifact> a) {
	weight += a->getWeight();
	items.push_back(std::move(a));
	return weight;
}

std::unique_ptr<Artifact> Inventory::drop(int itemIndex) {
	weight -= items[itemIndex]->getWeight();
	auto item = std::move(items[itemIndex]);
	items.erase(items.begin() + itemIndex);
	return item;
}

double Inventory::getWeight(){
	return weight;
}

void Inventory::saveState(std::ofstream& out) {
	out << "Inventory\n";
	for (auto it = items.begin(); it != items.end(); ++it) {
		(*it)->saveState(out);
	}
	out << "EndInventory\n";
}

void Inventory::clear() {
	weight = 0;
	items.clear();
}

int Inventory::getSize(){
	return items.size();
}

void Inventory::loadState(std::ifstream& in) {
	clear();
	std::string line;
	std::getline(in, line); //header
	std::getline(in, line); //EndInventory or first item name
	while (line != "EndInventory") {
		auto item = toArtifact(createGameItem(line));
		add(std::move(item));
		std::getline(in, line); //EndInventory or next item name
	}
}
