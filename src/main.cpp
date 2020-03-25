//============================================================================
// Name        : main.cpp
// Author      : Jesse Farnham
//============================================================================

#include <string>
#include "Marooned.h"

int main( int argc, char* args[] )
{
	Marooned game(0);

	//Start up SDL and create window
	if( !game.initSDL() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		game.initGame();
		game.mainLoop();
	}

	//Free resources and close SDL
	game.close();

	return 0;
}
