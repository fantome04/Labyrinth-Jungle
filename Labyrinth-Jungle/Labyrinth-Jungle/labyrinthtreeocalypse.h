#ifndef TREEOCALYPSE_H
#define TREEOCALYPSE_H

#include "labyrinth.h"

class LabyrinthTreeocalypse : public Labyrinth
{
public:

	LabyrinthTreeocalypse();
	~LabyrinthTreeocalypse() = default;

	virtual void generate_labyrinth() override; //generates labyrinth using dfs
	virtual void plant_trees() override; //plants 3 trees in random locations
	virtual void update_trees() override; //calls the update method for all trees

private:
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start); //dfs labyrinth generation starting at 'start'
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start); //helper functions
	void shuffle(std::vector<int>& visit_order); //helper function
	void generate_exits(); //generates exit location(s)
	void compare_exits(); //checks if 2 exits can exist together
	void starting_trees(); //fills the tree vector at the start of the game
};

#endif // !TREEOCALYPSE_H
