/*
 * Map.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: jesse
 */

#include "Map.h"
#include "BareGround.h"

const int TILE_SIZE = 20;

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
  int locR = 0;
  int locC = 0;
  for (int r = 0; r < size; r++) {
	  for (int c = 0; c < size; c++) {
		  GameItem& itemAtLoc = *state[r][c];
		  Texture texture = textureLoader.getPersistedTextureWithName(itemAtLoc.getTextureName());
		  texture.render(locC + 1, locR + 1, locC + TILE_SIZE - 1, locR + TILE_SIZE - 1, 0., NULL, SDL_FLIP_NONE);
		  locC += TILE_SIZE;
	  }
	  locR += TILE_SIZE;
	  locC = 0;
  }
}

Map::~Map() {
}

