// Dungeon Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Dice.h"
#include "Player.h"
#include "Game.h"

#include <iostream>
#include <time.h>



int main()
{
	Game* game;

    game = new Game;



    game->InitializeRooms();
	game->StartGame();
	//debug. Check if player was initialized properly and we can access everything
	cout << "Skill: " << game->player1->getSkill() << endl;
	cout << "Stamina: " << game->player1->getStamina() << endl;
	cout << "Luck: " << game->player1->getLuck() << endl;
	cout << "Supplies: " << game->player1->getSupplies() << endl;

	while (game->gamePlaying)
	{
		cout << endl;
		cout << "What do you want to do?" << endl;
		cout << endl;
		game->ProcessInput(game->HandleInput());
	}

	delete (game);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
