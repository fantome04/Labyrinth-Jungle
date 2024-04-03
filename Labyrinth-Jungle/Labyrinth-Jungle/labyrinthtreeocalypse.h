#ifndef TREEOCALYPSE_H
#define TREEOCALYPSE_H

#include "labyrinth.h"

class LabyrinthTreeocalypse : public Labyrinth
{
public:

	LabyrinthTreeocalypse();
	~LabyrinthTreeocalypse() = default;

	virtual void generate_labyrinth() override;
	virtual void plant_trees() override;
	virtual void update_trees() override;

private:
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start);
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start);
	void shuffle(std::vector<int>& visit_order);
	void generate_exits();
	void compare_exits();
	void starting_trees(); 
};

#endif // !TREEOCALYPSE_H
