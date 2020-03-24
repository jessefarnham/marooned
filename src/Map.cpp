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

Map::~Map() {
}

