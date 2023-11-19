#include "Player.h"
#include "Dice.h"

void Player::InitializeStats()
{
	skill = Dice::RollD6(6);
	stamina = Dice::Roll2D6(12);
	luck = Dice::RollD6(6);

	originalSkill = skill;
	originalStamina = stamina;
	originalLuck = luck;
}

void Player::Health()
{
	cout << "Player's health is: " << stamina << "\n";
}

bool Player::TestLuck(){
	bool success;

	if (Dice::Roll2D6() <= luck)
	{
		success = true;
		cout << "You were lucky!" << endl;
	}
	else
	{
		success = false;
		cout << "You were unlucky!" << endl;
	}

	setLuck(luck - 1);
	cout << "Your luck is now " << luck << endl;

	return success;
}

void Player::TakeDamage(int damage)
{
	stamina = stamina - damage;

	if (stamina < 0)
	{
		stamina = 0;
	}
}

void Player::eatSupplies() {
	if (supplies > 0)
	{
		supplies--;
		stamina += 4;
	}
	else
	{
		cout << "No supplies!" << endl;
	}
}

void Player::givePotion(string type) {
	if (type == "skill")
	{
		skillPotion += 2;
	}
	else if (type == "stamina")
	{
		stamPotion += 2;
	}
	else if (type == "luck")
	{
		luckPotion += 2;
	}
	else
	{
		return;
	}
}

void Player::drinkPotion(string type) {
	if (type == "skill" && skillPotion < 0)
	{
		skill = originalSkill;
		skillPotion--;
	}
	else if (type == "stamina" && stamPotion < 0)
	{
		stamina = originalStamina;
		stamPotion--;
	}
	else if (type == "luck" && luckPotion < 0)
	{
		luck = originalLuck;
		luckPotion--;
	}
	else
	{
		cout << "You don't have that potion!" << endl;
		return;
	}
}