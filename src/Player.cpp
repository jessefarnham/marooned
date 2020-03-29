/*
 * Player.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: jesse
 */

#include "Player.h"

Player::Player(double baseMaxCarry) {
	health = 100;
	food = 100;
	water = 100;
	this->baseMaxCarry = baseMaxCarry;
}

double Player::getMaxCarryWeight(){
	return baseMaxCarry;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

int Player::getHealth(){
	return health;
}

int Player::getFoodStatus(){
	return food;
}


int Player::getWaterStatus(){
	return water;
}

std::unique_ptr<Artifact> Player::pickUp(std::unique_ptr<Artifact> item){
	if (inventory.getWeightIfAdd(*item) <= getMaxCarryWeight()) {
		inventory.add(std::move(item));
		return nullptr;
	}
	else {
		return std::move(item);
	}
}

std::unique_ptr<Artifact> Player::drop(int itemIndex){
	if (itemIndex >= 0 && itemIndex < inventory.getSize()){
		return std::move(inventory.drop(itemIndex));
	}
	else{
		return nullptr;
	}
}

void Player::saveState(std::ofstream& out) {
	out << "Player\n";
	out << health << "\n";
	out << food << "\n";
	out << water << "\n";
	out << baseMaxCarry << "\n";
	inventory.saveState(out);
}

void Player::loadState(std::ifstream& in){
	std::string line;
	std::getline(in, line); //header
	in >> health;
	in >> food;
	in >> water;
	in >> baseMaxCarry;
	std::getline(in, line); //header
	inventory.loadState(in);
	std::getline(in, line); // trailing newline
}
