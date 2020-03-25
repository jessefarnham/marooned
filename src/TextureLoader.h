/*
 * TextureLoader.h
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#ifndef SRC_TEXTURELOADER_H_
#define SRC_TEXTURELOADER_H_

#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include <memory>

class TextureLoader {
public:
	TextureLoader(SDL_Renderer* renderer, TTF_Font* font);
	virtual ~TextureLoader();
	Texture& getPersistedTextureWithName(std::string name);
	Texture& getPersistedTextureFromText(std::string text);
	std::unique_ptr<Texture> getTextureFromText(std::string text);


private:
	std::unordered_map<std::string, std::unique_ptr<Texture>> imgTextures;
	std::unordered_map<std::string, std::unique_ptr<Texture>> textTextures;
	SDL_Renderer* renderer;
	TTF_Font* font;
};

#endif /* SRC_TEXTURELOADER_H_ */
