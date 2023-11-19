#pragma once
#include <iostream>

using namespace std;

class Player
{
public:
	Player() {
		InitializeStats();
	}
	int getLuck() {
		return luck;
	}
	void setLuck(int l) {
		luck = l;
	}
	int getStamina() {
		return stamina;
	}
	void setStamina(int s) {
		stamina = s;
	}
	int getSkill() {
		return skill;
	}
	void setSkill(int s) {
		skill = s;
	}
	int getSupplies() {
		return supplies;
	}
	void setSupplies(int s) {
		supplies = s;
	}
	void givePotion(string type);
	void drinkPotion(string type);
	void TakeDamage(int damage);
	void Health();
	bool TestLuck();
	void eatSupplies();

private:
	void InitializeStats();
	int originalLuck;
	int originalStamina;
	int originalSkill;
	int luck;
	int skill;
	int stamina;
	int stamPotion;
	int skillPotion;
	int luckPotion;
	int supplies;
};
