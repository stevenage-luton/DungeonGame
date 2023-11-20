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
		if (currentRoom->skillType != "" && !currentRoom->attempted)
		{
			cout << currentRoom->getPrompt() << endl;
		}
		//cout << "What do you want to do?" << endl;
		//ProcessInput(HandleInput());
	}
	void InitializeRooms() {
		srand(time(NULL));
		player1 = new Player;

		Room* room1 = new Room("FirstRoom", "The room is dark. You can see an entrance to the north.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "","","","","");

		Room* room2 = new Room("GoblinRoom", "The room is light. You can see an entrance to the south. There are also entrances East and West. Growling comes from the west doorway.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Room* room3 = new Room("Right1", "The room is eerily quiet, lit by torches that have burned away almost entirely. The only sound is water dripping from the roof.\n\nYou can see a doorway to the west, and a half-collapsed doorway to the east.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Room* room4 = new Room("Right2", "You are surrounded by mostly rubble. The room appears to have collapsed. Beams of light can be seen through the remains of the roof. \n\n You can see a half-collapsed doorway to the west, and a menacing door to the north.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Room* room5 = new Room("MinotaurRoom", "The Arena is empty now. It's eerily quiet.", nullptr, nullptr, nullptr, nullptr, nullptr, 20, "stamina", "You pull the lever with all your might.\n\nIt works! A small nook opens up in the corner of the Arena. Inside is a Stamina Potion.", "You pull with all your might. \n \n You strain yourself so hard you injure yourself.", "staminaPotion","With the Minotaur gone, you can examine the room more carefully.\n \n You see a lever shrouded in shadow.");

		Room* room6 = new Room("Left1", "The growling grows louder. You see doors to the north, east, and west.", nullptr, nullptr, nullptr, nullptr, nullptr, 18, "skill", "You disarm the traps and open the chest.\n\nInside is a stamina potion!", "You fail to disarm the trap. An arrow shoots out from the wall and sticks into your shoulder.", "staminaPotion","A chest is sitting conspicuously in the middle of the room.");

		Room* room7 = new Room("NinjaRoom", "The room is very dark. The corpse of the ninja lies motionless.\n\nThere is an exit to the east.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Room* room8 = new Room("Left1Up", "The growling is a roar now. There are entrances south, west, and north.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Room* room9 = new Room("ScorpionRoom", "The scorpion is still twitching slightly.\n\nThere is a doorway to the east.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Room* room10 = new Room("DragonRoom", "The Dragon lies dead. There's a door to the south, and the door to the end of the dungeon to the east. It's locked, and has a big trophy shaped hole in it. Take the trophy and then go east!", nullptr, nullptr, nullptr, nullptr, nullptr, 18, "skill", "You notice that the pedastal is trapped at the last moment, and replace the trophy with a perfectly weighted amount of sand.\n\nCongrats, now you just need to go east to the victory room!", "As you touch the trophy, you realize too late that the pedastal it's on is trapped. You lift the trophy off, and a boulder falls on you and kills you.", "victory","You're almost there! You just need to interact with the trophy to win.");

		//Room* room11 = new Room("WinRoom", "The room is light. You can see an entrance to the south.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "","");

		Monster* goblin = new Monster("Goblin", 5, 5);
		Monster* ninja = new Monster("Ninja", 9, 6);
		Monster* scorpion = new Monster("Giant Scorpion", 8, 10);
		Monster* minotaur = new Monster("Minotaur", 10, 10);
		Monster* dragon = new Monster("Dragon", 12, 16);

		room1->North = room2;
		room2->South = room1;
		room2->East = room3;
		room2->West = room6;
		room3->West = room2;
		room3->East = room4;
		room4->North = room5;
		room5->South = room4;
		room6->West = room7;
		room6->East = room2;
		room6->North = room8;
		room7->East = room6;
		room8->North = room10;
		room8->West = room9;
		room8->South = room6;
		room9->East = room8;
		room10->South = room8;

		room2->roomMonster = goblin;
		room5->roomMonster = minotaur;
		room7->roomMonster = ninja;
		room10->roomMonster = dragon;
		room9->roomMonster = scorpion;

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
					gamePlaying = false;
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
		else if (strInput == "interact")
		{
			if (currentRoom->skillType != "")
			{
				if (!currentRoom->attempted)
				{
					if (currentRoom->skillType == "skill")
					{
						SkillCheck(Dice::Roll2D6(player1->getSkill()));
					}else if (currentRoom->skillType == "stamina")
					{
						SkillCheck(Dice::Roll2D6(player1->getStamina()));
					}
					else if (currentRoom->skillType == "luck")
					{
						SkillCheck(Dice::Roll2D6(player1->getLuck()));
					}
				}
				else
				{
					cout << "You've already tried that." << endl;
				}
			}
			else
			{
				cout << "Nothing in this room to interact with." << endl;
			}
		}
		else if (strInput == "inventory")
		{
			cout << "Stats:" << endl;
			cout << "Skill: " << player1->getSkill() << endl;
			cout << "Stamina: " << player1->getStamina() << endl;
			cout << "Luck: " << player1->getLuck() << endl;
			cout << endl;
			cout << "Inventory:" << endl;
			cout << "Supplies: " << player1->getSupplies() << endl;
			cout << "Skill Potion Doses Left: " << player1->getSkillPotion() << endl;
			cout << "Stamina Potion Doses Left: " << player1->getStamPotion() << endl;
			cout << "Luck Potion Doses Left: " << player1->getLuckPotion() << endl;
		}
		else
		{
			cout << "Unable to interpret what you typed. Available commands: move/go DIRECTION, drink, eat, save,inventory, interact (if there's something to interact with)." << endl;
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
						player1 = new Player(fileContents);
						ChangeRoom(room);
					}
				}
			}
			else
			{
				cout << "Temp wasn't currentroom for some reason." << endl;
			}
			//player1 = new Player(fileContents);
		}
		else
		{
			cout << "File loaded incorrectly." << endl;
		}
		

	}
	void SkillCheck(int roll) {

		currentRoom->attempted = true;
		int health = player1->getStamina();
		if (roll >= currentRoom->skillReq)
		{
			cout << currentRoom->getSuccessMessage() << endl;
			if (currentRoom->getRewardType() == "skillPotion")
			{
				player1->givePotion("skill");
			}
			else if (currentRoom->getRewardType() == "staminaPotion")
			{
				player1->givePotion("stamina");
			}
			else if (currentRoom->getRewardType() == "luckPotion")
			{
				player1->givePotion("luck");
			}
			else if (currentRoom->getRewardType() == "victory")
			{
				Room* room11 = new Room("WinRoom", "The room is light. You can see an entrance to the south.", nullptr, nullptr, nullptr, nullptr, nullptr, NULL, "", "", "", "", "");
				currentRoom->East = room11;
			}
		}
		else
		{
			cout << currentRoom->getFailMessage() << endl;
			if (currentRoom->getRewardType() == "skillPotion")
			{
				int currSkill = player1->getSkill();
				player1->setSkill(currSkill -=2);
			}
			else if (currentRoom->getRewardType() == "staminaPotion")
			{
				player1->TakeDamage(4);
				health = player1->getStamina();
				if (health == 0)
				{
					cout << "You died." << endl;
					gamePlaying = false;
				}
			}
			else if (currentRoom->getRewardType() == "luckPotion")
			{
				int currSkill = player1->getSkill();
				player1->setSkill(currSkill -= 1);
				player1->TakeDamage(2);
				health = player1->getStamina();
				if (health == 0)
				{
					cout << "You died." << endl;
					gamePlaying = false;
				}
			}
		}
	}
};