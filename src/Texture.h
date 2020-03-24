/*
 * Texture.h
 *
 *  Created on: Mar 24, 2020
 *      Author: jesse
 */

#ifndef SRC_TEXTURE_H_
#define SRC_TEXTURE_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Texture
{
	public:
		//Initializes variables
		Texture(SDL_Renderer* renderer, TTF_Font* font);

		//Deallocates memory
		virtual ~Texture();

		//Loads image at specified path
		bool loadFromFile( std::string path);

		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Renders texture at given point
		void render( int x, int y, int w, int h,
				double angle = 0.0, SDL_Point* center = NULL,
				SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		SDL_Renderer* renderer;
		TTF_Font* font;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif /* SRC_TEXTURE_H_ */
