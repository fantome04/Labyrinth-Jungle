#include "game.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

void Game::play()
{
	if (mode_ == GameMode::TREEOCALYPSE)
		treeocalypse_game_loop();
	else
		wttj_game_loop();
}


void Game::treeocalypse_game_loop()
{
	while (!game_over_)
	{
		maze_.print();
		treeocalypse_update();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		Sleep(75);
	}
}

void Game::wttj_game_loop()
{
}

void Game::treeocalypse_update()
{
	char press = ' ';
	if (_kbhit())
		press = _getch();
	switch (press)
	{
	case 'w':
		//maze_.move_player('U');
		break;
	case 'd':
		//maze_.move_player('R');
		break;
	case 's':
		//maze_.move_player('D');
		break;
	case 'a':
		//maze_.move_player('L');
		break;
	default:
		break;
	}
}

void Game::prologue()
{
	//TODO some sort of start screen
	std::cout << "Choose game mode\n1. Treeocalypse\n2.Welcome to the jungle\n";
	int input;
	std::cin >> input;
	if (input == 1)
		mode_ = GameMode::TREEOCALYPSE;
	else if (input == 2)
		mode_ = GameMode::WTTJ;
}

void Game::epilogue()
{
}
