#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Player
{
public:
	Player() {
		InitializeStats();
	}
	Player(vector<string> data) {
		string delimiter = ":";
		for (string var : data) {
			string variable = var.substr(0, var.find(delimiter));
			string data = var.substr(var.find(delimiter) + 1, var.length());
			if (variable == "originalLuck")
			{
				originalLuck = stoi(data);
			}
			else if (variable == "originalStamina")
			{
				originalStamina = stoi(data);
			}
			else if (variable == "originalSkill")
			{
				originalSkill = stoi(data);
			}
			else if (variable == "luck")
			{
				luck = stoi(data);
			}
			else if (variable == "stamina")
			{
				stamina = stoi(data);
			}
			else if (variable == "skill")
			{
				skill = stoi(data);
			}
			else if (variable == "luckPotion")
			{
				luckPotion = stoi(data);
			}
			else if (variable == "staminaPotion")
			{
				stamPotion = stoi(data);
			}
			else if (variable == "skillPotion")
			{
				skillPotion = stoi(data);
			}
			else if (variable == "supplies")
			{
				supplies = stoi(data);
			}
		}
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
	int getOriginalSkill() {
		return originalSkill;
	}
	int getOriginalStamina() {
		return originalStamina;
	}
	int getOriginalLuck() {
		return originalLuck;
	}
	int getSkillPotion() {
		return skillPotion;
	}
	int getStamPotion() {
		return stamPotion;
	}
	int getLuckPotion() {
		return luckPotion;
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
