#ifndef __MINES_GAME_H
#define __MINES_GAME_H

#include <iostream>
#include <string>
#include <sstream>

#include "types.h"
#include "helperClasses.h"

#define DEFAULT_GAME_X     8
#define DEFAULT_GAME_Y     8
#define DEFAULT_GAME_BOMBS 10

class MinesGame
{
private:
	Vector2* gameSize;
	uint_8* playField;
	uint_8* printField;
	uint_16 arraySize;
	bool playerIsDeath;
	uint_8 numberOfMines;
	uint_16 numberOfFieldsLeft;

	Vector2 getCoordinate(std::string input);
	void setChar(Vector2 input, int_8 character);
	bool removeGround(Vector2 coordinate);
	void printGame();
	void setupPlayField();
	bool vectorInPlayField(Vector2 vector);
public:
	MinesGame(Vector2* gameSize, int_8 numberOfMines);
	bool nextGameStep();
};

#endif
