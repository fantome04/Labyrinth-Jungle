#ifndef JUNGLE_H
#define JUNGLE_H

#include "labyrinth.h"

class LabyrinthJungle : public Labyrinth
{
public:
	LabyrinthJungle();
	~LabyrinthJungle() = default;

	virtual void generate_labyrinth() override;
	virtual void update_trees() override;
	virtual void plant_trees() override;

	bool cut_tree(const Coordinate& coord, char dir);
	void restore_tree(const Coordinate& coord, char dir);

private:
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start); //generate labyrinth with dfs
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start); //helper function
	void shuffle(std::vector<int>& visit_order); //helper function
	void generate_exits(); //generates exit(s) on board
	void compare_exits(); //compares exit locations with each other
	void starting_trees(); //creates vector of trees at the start of the game
};

#endif // !JUNGLE_H
