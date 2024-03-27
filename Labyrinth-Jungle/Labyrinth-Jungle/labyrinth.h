#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <vector>

class Labyrinth
{
public:

	Labyrinth();

	void print();

private:

	void get_path(std::vector<std::pair<int, int>>& path, const std::pair<int, int> start, const std::pair<int, int> end);
	void dfs(std::vector<std::vector<char>>& board_copy, std::vector<char>& visited, const std::pair<int, int> start, const std::pair<int, int> end, char prev);

	const int board_size_ = 20;
	std::vector<std::vector<char>> board_;
	int number_of_exits_;
	std::vector<std::pair<int, int>> exits_;
};

#endif