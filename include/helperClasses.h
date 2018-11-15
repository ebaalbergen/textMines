#ifndef __MINES_HELPERCLASSES_H
#define __MINES_HELPERCLASSES_H

struct Vector2
{
	public:
		Vector2(int x, int y);
		int x;
		int y;
};

class RandomGenerator
{
	public:
		RandomGenerator();
		int getNumber(int maximum);
};

#endif

