/*
 * Map.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#include <climits>
#include "Map.h"
#include "BareGround.h"
#include "ImpassableTerrain.h"
#include "util.h"
#include "artifacts/Artifact.h"
#include "artifacts/Bolts.h"


Map::Map(int size, int visibleSize, int tileSize) {
	this->size = size;
	this->visibleSize = visibleSize;
	this->tileSize = tileSize;
}

void Map::createEmpty() {
	state.resize(size);
	for (int r = 0; r < size; r++) {
		state[r].resize(size);
		for (int c = 0; c < size; c++) {
			auto bareGround = std::make_unique<BareGround>();
			state[r][c].resize(1);
			state[r][c][0] = std::move(bareGround);
		}
	}
}

void Map::createRandom(double fracImpassable, double fracArtifact) {
	state.resize(size);
		for (int r = 0; r < size; r++) {
			state[r].resize(size);
			for (int c = 0; c < size; c++) {
				std::unique_ptr<GameItem> gameObj;
				if (util::randFloat() < fracImpassable) {
					gameObj = std::make_unique<ImpassableTerrain>();
				}
				else {
					gameObj = std::make_unique<BareGround>();
				}
				state[r][c].resize(1);
				state[r][c][0] = std::move(gameObj);
			}
		}
	placeArtifacts(fracArtifact);
}

void Map::placeArtifacts(double fracArtifact) {
	for (int r = 0; r < size; r++){
		for (int c = 0; c < size; c++) {
			std::unique_ptr<Artifact> artifact;
			if (util::randFloat() < fracArtifact){
				artifact = std::make_unique<Bolts>(100, 0.01);
				state[r][c].push_back(std::move(artifact));
			}
		}
	}
}

bool Map::isStandable(int r, int c) {
	for (auto it = state[r][c].begin(); it != state[r][c].end(); it++) {
		if (!(*it)->getStandable())
			return false;
	}
	return true;
}

bool Map::placePlayer(int r, int c) {
	if (isStandable(r, c)) {
		playerLoc = std::make_pair(r, c);
		return true;
	}
	else {
		return false;
	}
}

GameItem& Map::getHighestPriorityItem(int r, int c) {
	int maxPrio = (INT_MIN);
	int iMax = -1;
	int i = 0;
	for (auto it = state[r][c].begin(); it != state[r][c].end(); i++, it++) {
		int prio = (*it)->getDrawPriority();
		if (prio > maxPrio) {
			iMax = i;
			maxPrio = prio;
		}
	}
	return *state[r][c][iMax];
}

void Map::render(TextureLoader& textureLoader){
  Texture& playerTexture = textureLoader.getPersistedTextureWithName("player");
  for (int r = 0; r < visibleSize; r++) {
	  for (int c = 0; c < visibleSize; c++) {
		  int locR = r * tileSize;
		  int locC = c * tileSize;
		  int mapR = playerLoc.first - (visibleSize / 2) + r;
		  int mapC = playerLoc.second - (visibleSize / 2) + c;
		  auto mapLoc = std::make_pair(mapR, mapC);
		  Texture* textureToRender;
		  if (playerLoc == mapLoc){
			  textureToRender = &playerTexture;
		  }
		  else if (isInBounds(mapLoc)){
			  GameItem& itemAtLoc = getHighestPriorityItem(mapR, mapC);
			  textureToRender = &textureLoader.getPersistedTextureWithName(itemAtLoc.getTextureName());
		  }
		  else {
			  textureToRender = NULL;
		  }
		  if (textureToRender){
			  textureToRender->render(locC, locR, tileSize - 1, tileSize - 1);
		  }
	  }
  }
}

bool Map::movePlayerLeft() {
	auto newLoc = std::make_pair(playerLoc.first, playerLoc.second - 1);
	return tryMovePlayer(newLoc);
}

bool Map::movePlayerRight() {
	auto newLoc = std::make_pair(playerLoc.first, playerLoc.second + 1);
	return tryMovePlayer(newLoc);
}

bool Map::movePlayerUp() {
	auto newLoc = std::make_pair(playerLoc.first - 1, playerLoc.second);
	return tryMovePlayer(newLoc);
}

bool Map::movePlayerDown() {
	auto newLoc = std::make_pair(playerLoc.first + 1, playerLoc.second);
	return tryMovePlayer(newLoc);
}

bool Map::tryMovePlayer(std::pair<int, int> newLoc) {
	if (isInBounds(newLoc) && isStandable(newLoc.first, newLoc.second)) {
			placePlayer(newLoc.first, newLoc.second);
			return true;
		}
		else {
			return false;
		}
}

bool Map::isInBounds(std::pair<int ,int> loc) {
	return (loc.first >= 0 && loc.first < size && loc.second >= 0 && loc.second < size);
}

void Map::saveState(std::ofstream& out) {
	out << "Map\n";
	out << playerLoc.first << "\n";
	out << playerLoc.second << "\n";
}

void Map::loadState(std::ifstream& in) {
	std::string line;
	int playerR;
	int playerC;
	getline(in, line); //header
	in >> playerR;
	in >> playerC;
	getline(in, line); //trailing newline
	placePlayer(playerR, playerC);
}

void Map::examine(MessageQueue& mq){
	mq.postMessage("You see the following:");
	auto& itemVector = state[playerLoc.first][playerLoc.second];
	for (auto it = itemVector.begin(); it != itemVector.end(); it++) {
		mq.postMessage((*it)->getDescription());
	}
}

Map::~Map() {
}

