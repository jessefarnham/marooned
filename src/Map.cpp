/*
 * Map.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#include "Map.h"
#include "BareGround.h"

const int TILE_SIZE = 10;

Map::Map(int size) {
	this->size = size;
}

void Map::createEmpty() {
	state.resize(size);
	for (int r = 0; r < size; r++) {
		state[r].resize(size);
		for (int c = 0; c < size; c++) {
			auto bareGround = std::make_unique<BareGround>();
			state[r][c] = std::move(bareGround);
		}
	}
}

bool Map::placePlayer(int r, int c) {
	if (state[r][c]->getStandable()) {
		playerLoc = std::make_pair(r, c);
		return true;
	}
	else {
		return false;
	}
}

void Map::render(TextureLoader& textureLoader){
  Texture& playerTexture = textureLoader.getPersistedTextureWithName("player");
  for (int r = 0; r < size; r++) {
	  for (int c = 0; c < size; c++) {
		  int locR = r * TILE_SIZE;
		  int locC = c * TILE_SIZE;
		  Texture* textureToRender;
		  if (playerLoc == std::make_pair(r, c)){
			  textureToRender = &playerTexture;
		  }
		  else {
			  GameItem& itemAtLoc = *state[r][c];
			  textureToRender = &textureLoader.getPersistedTextureWithName(itemAtLoc.getTextureName());
		  }
		  textureToRender->render(locC, locR, TILE_SIZE - 1, TILE_SIZE - 1, 0., NULL, SDL_FLIP_NONE);
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
	if (isInBounds(newLoc) && state[newLoc.first][newLoc.second]->getStandable()) {
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

Map::~Map() {
}

