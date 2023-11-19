#include "Monster.h"
#include "Dice.h"

void Monster::Health()
{
	cout << "Monster's health is: " << stamina << "\n";
}

void Monster::TakeDamage(int damage)
{
	stamina = stamina - damage;

	if (stamina < 0)
	{
		stamina = 0;
	}
}