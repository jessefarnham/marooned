//============================================================================
// Name        : main.cpp
// Author      : Jesse Farnham
//============================================================================

#include "Marooned.h"


int main( int argc, char* args[] )
{
	Marooned game(0);

	//Start up SDL and create window
	if( !game.init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		game.mainLoop();
	}

	//Free resources and close SDL
	game.close();

	return 0;
}
