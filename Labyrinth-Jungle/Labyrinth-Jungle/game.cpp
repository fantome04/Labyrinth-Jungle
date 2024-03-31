#include "game.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

Game::Game()
	:game_over_(false)
	,win(false)
	,mode_(GameMode::TREEOCALYPSE)
	,maze_()
{
	
}

void Game::play()
{
	if (mode_ == GameMode::TREEOCALYPSE)
		treeocalypse_game_loop();
	else
		wttj_game_loop();

	epilogue();
}


void Game::treeocalypse_game_loop()
{
	//maze_.print();
	while (!game_over_)
	{
		maze_.print();
		treeocalypse_update();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		
		Sleep(150);
		if (!maze_.path_open())
		{
			game_over_ = true;
			//system("cls");
		}
	}
}

void Game::wttj_game_loop()
{
}

void Game::treeocalypse_update()
{
	//Coordinate prev = maze_.get_player_coordinates();
	bool moved = maze_.move_player(read_input());
	maze_.update(moved);

}

char Game::read_input()
{
	char press = ' ';
	if (_kbhit()) {
		press = _getch();
	}
	return press;
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
	system("cls");
	std::cout << "Game Over" << std::endl;
}
