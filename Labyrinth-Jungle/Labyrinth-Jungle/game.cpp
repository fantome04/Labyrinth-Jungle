#include "game.h"
#include "lumberjackplayer.h"
#include "labyrinthjungle.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

Game::Game()
	:game_over_(false)
	,win_(false)
	,mode_(GameMode::TREEOCALYPSE)
{
	prologue();
	if (mode_ == GameMode::TREEOCALYPSE)
	{
		human_ = new HumanPlayer({ 10, 10 });
		maze_ = new LabyrinthTreeocalypse();
	}
	else
	{
		human_ = new LumberjackPlayer({10,10});
		maze_ = new LabyrinthJungle();
	}
	generate_player();
	maze_->set_player_coord(human_->get_coord());
	system("cls");
}

void Game::play()
{
	game_loop();
	if (win_)
	{
		epilogue_win();
	}
	else
	{
		epilogue_lose();
	}
}

Game::~Game()
{
	delete maze_;
	delete human_;
}


void Game::game_loop()
{
	while (!game_over_)
	{
		maze_->print();
		if(mode_ == GameMode::TREEOCALYPSE)
		{
			treeocalypse_update();
		}
		else
		{
			jungle_update();
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		Sleep(150);
		if (player_on_exit())
		{
			game_over_ = true;
			win_ = true;
		}
		if (!maze_->path_open())
		{
			game_over_ = true;
			win_ = false;
		}
	}
}

void Game::treeocalypse_update()
{
	Coordinate before = human_->get_coord();

	bool moved = false;
	if (human_->move(read_input()))
	{
		Coordinate coord = human_->get_coord();
		auto board_ = maze_->get_board();
		if (board_[coord.first][coord.second] != '#')
		{
			moved = true;
			maze_->set_player_coord(human_->get_coord());
		}
	}
	if (!moved)
	{
		human_->set_coord(before);
	}
	maze_->update(moved);

}

void Game::jungle_update()
{
	Coordinate before = human_->get_coord();

	bool moved = false;
	char input = read_input();
	
	if(dynamic_cast<LumberjackPlayer*>(human_)->cuts_left()){
		if (input == 'r')
		{
			char facing = dynamic_cast<LumberjackPlayer*>(human_)->facing();
			if (dynamic_cast<LabyrinthJungle*>(maze_)->cut_tree(before, facing))
			{
				dynamic_cast<LumberjackPlayer*>(human_)->cut();

			}
		}
	}
	else
	{
		if (!dynamic_cast<LabyrinthJungle*>(maze_)->bfs_called())
		{
			std::vector<Coordinate> temp;
			std::vector<Coordinate> exits = maze_->get_exits();
			for (int i = 0; i < exits.size(); ++i)
			{
				maze_->get_path(human_->get_coord(), exits[i], temp);
			}

			if (temp.empty())
			{
				game_over_ = true;
				win_ = false;
				return;
			}
		}
	}

	
	if (human_->move(input))
	{
		Coordinate coord = human_->get_coord();
		auto board_ = maze_->get_board();
		if (board_[coord.first][coord.second] != '#')
		{
			moved = true;
			maze_->set_player_coord(human_->get_coord());
		}
	}
	if (!moved)
	{
		human_->set_coord(before);
	}
	maze_->set_player_symbol(human_->get_symbol());
	maze_->update(moved);
}

char Game::read_input()
{
	char press = ' ';
	if (_kbhit()) 
	{
		press = _getch();
	}
	return press;
}

void Game::generate_player()
{
	Coordinate coord = human_->get_coord();

	auto board_ = maze_->get_board();

	bool is_set = true;

	if (board_[coord.first][coord.second] == '#')
	{
		is_set = false;
		std::vector<Coordinate> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };

		for (int i = 0; i < directions.size(); ++i)
		{
			int new_row = coord.first + directions[i].first;
			int new_column = coord.second + directions[i].second;

			if (board_[new_row][new_column] != '#')
			{
				human_->set_coord({ new_row, new_column });
			}
		}
	}

}

bool Game::player_on_exit() const
{
	auto exits_ = maze_->get_exits();
	for (const auto& x : exits_)
	{
		if (human_->get_coord() == x)
		{
			return true;
		}
	}
	return false;
}

void Game::prologue()
{
	//TODO some sort of start screen
	std::cout << "Choose game mode\n1. Treeocalypse\n2.Welcome to the jungle\n";
	int input;
	std::cin >> input;
	if (input == 1)
	{
		mode_ = GameMode::TREEOCALYPSE;
	}
	else if (input == 2)
	{
		mode_ = GameMode::JUNGLE;
	}
}

void Game::epilogue_win()
{
	system("cls");
	std::cout << "You won" << std::endl;
}

void Game::epilogue_lose()
{
	system("cls");
	std::cout << "Game Over" << std::endl;
}
