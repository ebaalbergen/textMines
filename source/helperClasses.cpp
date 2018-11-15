#include "../include/helperClasses.h"
#include <stdlib.h>
#include <time.h>

Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

RandomGenerator::RandomGenerator()
{

}

int RandomGenerator::getNumber(int maximum)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	srand((time_t)ts.tv_nsec);
	return rand() % maximum;
}
