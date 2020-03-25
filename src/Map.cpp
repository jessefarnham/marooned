/*
 * Map.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#include "Map.h"
#include "BareGround.h"
#include "ImpassableTerrain.h"
#include "util.h"

const int TILE_SIZE = 10;

Map::Map(int size, int visibleSize) {
	this->size = size;
	this->visibleSize = visibleSize;
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

void Map::createRandom(double fracImpassable) {
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
				state[r][c] = std::move(gameObj);
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
  for (int r = 0; r < visibleSize; r++) {
	  for (int c = 0; c < visibleSize; c++) {
		  int locR = r * TILE_SIZE;
		  int locC = c * TILE_SIZE;
		  int mapR = playerLoc.first - (visibleSize / 2) + r;
		  int mapC = playerLoc.second - (visibleSize / 2) + c;
		  auto mapLoc = std::make_pair(mapR, mapC);
		  Texture* textureToRender;
		  if (playerLoc == mapLoc){
			  textureToRender = &playerTexture;
		  }
		  else if (isInBounds(mapLoc)){
			  GameItem& itemAtLoc = *state[mapR][mapC];
			  textureToRender = &textureLoader.getPersistedTextureWithName(itemAtLoc.getTextureName());
		  }
		  else {
			  textureToRender = NULL;
		  }
		  if (textureToRender){
			  textureToRender->render(locC, locR, TILE_SIZE - 1, TILE_SIZE - 1, 0., NULL, SDL_FLIP_NONE);
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

