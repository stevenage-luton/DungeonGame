#pragma once

#include "Room.h"
#include "Dice.h"
#include "Player.h"
#include <stdlib.h>
#include <fstream>


class Game {
public:
	Game() : currentRoom(nullptr), player1(nullptr) {}
	Room* currentRoom;
	Player* player1;
	vector<Room*> rooms;
	bool gamePlaying = true;
	void ChangeRoom(Room* room) {
		system("cls");
		currentRoom = room;
		if (currentRoom->roomMonster != nullptr)
		{
			cout << "There is a " << currentRoom->roomMonster->getName() << " in the room." << endl;
			CombatEncounter(player1, currentRoom->roomMonster);
		}
		currentRoom->RenderRoom();
		//cout << "What do you want to do?" << endl;
		//ProcessInput(HandleInput());
	}
	void InitializeRooms() {
		srand(time(NULL));
		player1 = new Player;

		Room* room1 = new Room("FirstRoom", "The room is dark. You can see an entrance to the north.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "");

		Room* room2 = new Room("Room2", "The room is light. You can see an entrance to the south.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "");

		Monster* goblin = new Monster("Goblin", 5, 5);

		room1->North = room2;
		room2->South = room1;
		room2->roomMonster = goblin;

		rooms.push_back(room1);
		rooms.push_back(room2);


		//ChangeRoom(room1);

	}
	void CombatEncounter(Player* player, Monster* monster) {
		bool continueCombat = true;
		while (continueCombat)
		{
			cout << endl;
			cout << "What do you want to do? Attack, Drink Potion, Eat?" << endl;
			string action = HandleInput();
			cout << endl;
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
					cout << endl;
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
					cout << endl;
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
					cout << endl;
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
			else if (action == "drink potion" || action == "drink")
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
		cout << endl;
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
		else if (strInput == "move east" || strInput == "go east")
		{
			if (currentRoom->East != nullptr)
			{
				ChangeRoom(currentRoom->East);
			}
			else
			{
				cout << "No Room to the East." << endl;
			}
		}
		else if (strInput == "move west" || strInput == "go west")
		{
			if (currentRoom->West != nullptr)
			{
				ChangeRoom(currentRoom->West);
			}
			else
			{
				cout << "No Room to the West." << endl;
			}
		}
		else if (strInput == "drink potion" || strInput == "drink")
		{
			cout << "Which Potion? Skill, Stamina, Luck?" << endl;
			string action = HandleInput();
			if (action == "skill" || "stamina" || "luck")
			{
				player1->drinkPotion(action);
			}
			else
			{
				cout << "Please enter either skill, stamina, or luck." << endl;
			}
		}
		else if (strInput == "eat")
		{
			player1->eatSupplies();
		}
		else if (strInput == "save" || strInput == "save game")
		{
			ofstream SaveFile("saveFile.txt");
			if (SaveFile.fail())
			{
				cout << "Unable to Create File." << endl;
			}
			else
			{

				SaveFile << "currentroom:" << currentRoom->getTitle() << endl;
				SaveFile << "originalLuck:" << player1->getOriginalLuck() << endl;
				SaveFile << "originalStamina:" << player1->getOriginalStamina() << endl;
				SaveFile << "originalSkill:" << player1->getOriginalSkill() << endl;
				SaveFile << "luck:" << player1->getLuck() << endl;
				SaveFile << "stamina:" << player1->getStamina() << endl;
				SaveFile << "skill:" << player1->getSkill() << endl;
				SaveFile << "luckPotion:" << player1->getLuckPotion() << endl;
				SaveFile << "staminaPotion:" << player1->getStamPotion() << endl;
				SaveFile << "skillPotion:" << player1->getSkillPotion() << endl;
				SaveFile << "supplies:" << player1->getSupplies() << endl;

				SaveFile.close();
				cout << "Saved Game!" << endl;
			}
		}

		
	}
	void StartGame() {
		srand(time(NULL));

		string input;

		while (input != "new" && input != "new game" && input != "load" && input != "load game")
		{
			cout << "Would you like to start a New Game, or Load a previous game?" << endl;
			input = HandleInput();
		}
		if (input == "load" || input == "load game")
		{
			LoadGame();
		}
		else
		{
			player1 = new Player;
			string startingPotion;

			while (startingPotion != "skill" && startingPotion != "stamina" && startingPotion != "luck")
			{
				cout << "Which starting potion would you like? Skill, Luck, Stamina?" << endl;
				startingPotion = HandleInput();
				cout << endl;
			}
			player1->givePotion(startingPotion);
			ChangeRoom(*(rooms.begin()));
		}

		
	}
	void LoadGame() {
		ifstream SaveFile("saveFile.txt");
		vector<string> fileContents;
		string tempString;
		if (SaveFile.is_open())
		{
			while (getline(SaveFile, tempString))
			{
				fileContents.push_back(tempString);
			}
		}
		else
		{
			cout << "Unable to open file." << endl;
			return;
		}
		string delimiter = ":";
		if (!fileContents.front().empty())
		{
			string savedRoom = fileContents.front();
			string temp = savedRoom.substr(0, savedRoom.find(delimiter));
			string data = savedRoom.substr(savedRoom.find(delimiter) + 1, savedRoom.length());
			if (temp == "currentroom")
			{
				for (Room* room : rooms) {
					if (room->getTitle() == data)
					{
						ChangeRoom(room);
					}
				}
			}
			else
			{
				cout << "Temp wasn't currentroom for some reason." << endl;
			}
			player1 = new Player(fileContents);
		}
		else
		{
			cout << "File loaded incorrectly." << endl;
		}
		

	}
};