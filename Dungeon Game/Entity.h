#pragma once
#include <iostream>

using namespace std;

class Entity
{
public:
	Entity() {
		InitializeStats();
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

private:
	void InitializeStats() {

	};
	void Health();
	void TakeDamage(int damage);
	int originalStamina;
	int originalSkill;
	int skill;
	int stamina;
};
