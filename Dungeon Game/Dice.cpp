#include "Dice.h"



int Dice::RollD6()
{
	return rand() % 6 + 1;
}

int Dice::RollD6(int modifier)
{
	return (rand() % 6 + 1) + modifier;
}
int Dice::Roll2D6()
{
	return (rand() % 6 + 1) + (rand() % 6 + 1);
}
int Dice::Roll2D6(int modifier)
{
	return (rand() % 6 + 1) + (rand() % 6 + 1) + modifier;
}
