#ifndef TREEOCALYPSE_H
#define TREEOCALYPSE_H

#include "labyrinth.h"

class LabyrinthTreeocalypse : public Labyrinth
{
public:

	LabyrinthTreeocalypse();
	~LabyrinthTreeocalypse() = default;

	virtual void update(bool moved) override; //updates labyrinth
	virtual void generate_labyrinth() override; //generate labyrinth 
	virtual void plant_trees() override; //plants 3 trees in random places on the board
	virtual void update_trees() override; //calls update method for all trees

private:
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start); //generate labyrinth with dfs
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start); //helper function
	void shuffle(std::vector<int>& visit_order); //helper function
	void generate_exits(); //generates exit(s) on board
	void compare_exits(); //compares exit locations with each other
	void starting_trees(); //creates vector of trees at the start of the game
};

#endif // !TREEOCALYPSE_H
