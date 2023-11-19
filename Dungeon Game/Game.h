#pragma once

#include "Room.h"
#include "Dice.h"
#include "Player.h"
#include <stdlib.h>


class Game {
public:
	Room* currentRoom;
	Player* player1;

	void ChangeRoom(Room* room) {
		system("cls");
		currentRoom = room;
		if (currentRoom->roomMonster != nullptr)
		{
			cout << "There is a " << currentRoom->roomMonster->getName() << " in the room." << endl;
			CombatEncounter(player1, currentRoom->roomMonster);
		}
		currentRoom->RenderRoom();
		cout << "What do you want to do?" << endl;
		ProcessInput(HandleInput());
	}
	void InitializeRooms() {
		srand(time(NULL));
		player1 = new Player;

		Room room1("FirstRoom", "The room is dark. You can see an entrance to the north.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "");
		Room room2("Room2", "The room is light. You can see an entrance to the south.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "");

		Monster Goblin("Goblin", 7, 3);

		room1.North = &room2;
		room2.South = &room1;
		room1.roomMonster = &Goblin;

		ChangeRoom(&room1);

	}
	void CombatEncounter(Player* player, Monster* monster) {
		bool continueCombat = true;
		while (continueCombat)
		{
			cout << "What do you want to do? Attack, Drink Potion, Eat?" << endl;
			string action = HandleInput();
			if (action == "attack")
			{
				int monsterAttack = Dice::Roll2D6(monster->getSkill());
				int playerAttack = Dice::Roll2D6(player->getSkill());
				cout << monster->getName() << "'s roll + skill was: " << monsterAttack << endl;
				cout << "Your roll + skill was: " << playerAttack << endl;
				if (playerAttack > monsterAttack)
				{
					cout << "You have wounded the " << monster->getName() << " for 2 damage." << endl;
					monster->TakeDamage(2);
					cout << monster->getName() << "'s health is now " << monster->getStamina() << endl;
					if (monster->getStamina() != 0)
					{
						cout << "Try and use Luck to double damage? y/n" << endl;
						string action = HandleInput();
						if (action == "y")
						{
							if (player->TestLuck())
							{
								cout << "You have critically hit the " << monster->getName() << " for another 2 damage." << endl;
								monster->TakeDamage(2);
							}
							else
							{
								cout << "Your attack is weaker! " << monster->getName() << " only takes 1 damage!" << endl;
								monster->TakeDamage(-1);
							}
						}
					}			
				}
				else if (playerAttack < monsterAttack)
				{
					cout << monster->getName() << " has wounded you for 2 damage." << endl;
					player->TakeDamage(2);
					player->Health();
					cout << "Try and use Luck to half damage taken? y/n" << endl;
					string action = HandleInput();
					if (action == "y")
					{
						if (player->TestLuck())
						{
							cout << "You dodge and only take 1 damage!" << endl;
							player->TakeDamage(-1);
						}
						else
						{
							cout << "You dodge into the attack! You take 4 damage!" << endl;
							player->TakeDamage(2);
						}
					}
				}
				else if (playerAttack == monsterAttack)
				{
					cout << "You both miss." << endl;
				}

				if (monster->getStamina() == 0)
				{
					continueCombat = false;
					cout << "You kill the " << monster->getName() << "." << endl;
					currentRoom->roomMonster = nullptr;
				}
				if (player->getStamina() == 0)
				{
					continueCombat = false;
					cout << "You died." << endl;
				}
			}
			else if (action == "drink potion" || "drink")
			{
				cout << "Which Potion? Skill, Stamina, Luck?" << endl;
				string action = HandleInput();
				if (action == "skill" ||"stamina" || "luck")
				{
					player->drinkPotion(action);
				}
				else
				{
					cout << "Please enter either skill, stamina, or luck." << endl;
				}
			}
			else if (action == "eat")
			{
				player->eatSupplies();
			}
		}
	}
	string HandleInput() {
		string input;
		getline(cin, input);
		for (int i = 0; i < input.length(); i++) { 
			input[i] = tolower(input[i]);
		}

		return input;
		
	}
	void ProcessInput(string strInput) {

		cout << strInput;

		if (strInput == "move north" || strInput == "go north")
		{
			if (currentRoom->North != nullptr)
			{
				ChangeRoom(currentRoom->North);
			}
			else
			{
				cout << "No Room to the North." << endl;
			}
		}
		else if (strInput == "move south" || strInput == "go south")
		{	
			if (currentRoom->South != nullptr)
			{
				ChangeRoom(currentRoom->South);
			}
			else
			{
				cout << "No Room to the South." << endl;
			}		
		}
		
		
		
		
	}
};