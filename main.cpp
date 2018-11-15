#include "include/game.h"
#include "include/helperClasses.h"
#include "include/types.h"
#include <string.h>

Vector2* playfieldSize;
int_8 numberOfMines;

int main(int_32 argc, int_8** args)
{
	//See if there are arguments set for declaring the size of the playfield
	//and the number of bombs
	if(argc > 3)
	{
		//If so, use those values as the size of the playfield and the
		//number of bombs
		playfieldSize = new Vector2(atoi(args[1]), atoi(args[2]));
		numberOfMines = (int_8)atoi(args[3]);
	}
	else
	{
		//If not, default to the standard sizes
		playfieldSize = new Vector2(DEFAULT_GAME_X, DEFAULT_GAME_Y);
		numberOfMines = DEFAULT_GAME_BOMBS;
	}
	//Make a new game instance
	MinesGame* mineGame = new MinesGame(playfieldSize, numberOfMines);
	
	//prepare and go into the main gameloop
	bool gameRunning = true;
	while(gameRunning)
	{
		//Do the next gamestep
		gameRunning = mineGame->nextGameStep();
	}

	return 0;
}

