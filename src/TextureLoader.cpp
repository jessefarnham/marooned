/*
 * TextureLoader.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#include "TextureLoader.h"
#include "Texture.h"
#include <memory>

TextureLoader::TextureLoader(SDL_Renderer* renderer, TTF_Font* font) {
	this->renderer = renderer;
	this->font = font;
}

TextureLoader::~TextureLoader() {
	// TODO Auto-generated destructor stub
}

Texture& TextureLoader::getPersistedTextureWithName(std::string name) {
	if (!imgTextures.count(name)) {
		auto newTexture = std::make_unique<Texture>(renderer, font);
		newTexture->loadFromFile("./textures/" + name + ".bmp");
		imgTextures.insert(std::make_pair(name.c_str(), std::move(newTexture)));
	}
	return *imgTextures[name];
}

Texture& TextureLoader::getPersistedTextureFromText(std::string text) {
	if (!textTextures.count(text)) {
		auto newTexture = getTextureFromText(text);
		textTextures.insert(std::make_pair(text.c_str(), std::move(newTexture)));
	}
	return *textTextures[text];
}

std::unique_ptr<Texture> TextureLoader::getTextureFromText(std::string text) {
	auto newTexture = std::make_unique<Texture>(renderer, font);
	newTexture->loadFromRenderedText(text, {0xff, 0xff, 0xff, 0xff});
	return newTexture;
}

