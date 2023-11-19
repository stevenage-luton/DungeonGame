#pragma once

#include <iostream>
#include <string>

using namespace std;

class Monster
{
public:
	Monster(const string& name, int skill, int stamina) : name(name), skill(skill), stamina(stamina) {
		originalSkill = skill;
		originalStamina = stamina;
	};
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
	string getName() {
		return name;
	}
	void TakeDamage(int damage);

private:
	void Health();
	string name;
	int originalStamina;
	int originalSkill;
	int skill;
	int stamina;

};
