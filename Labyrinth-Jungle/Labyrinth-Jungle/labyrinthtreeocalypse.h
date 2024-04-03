#ifndef TREEOCALYPSE_H
#define TREEOCALYPSE_H

#include "labyrinth.h"

class LabyrinthTreeocalypse : public Labyrinth
{
public:

	LabyrinthTreeocalypse();
	~LabyrinthTreeocalypse() = default;

	virtual void print();
	virtual void update(bool moved);
	virtual Coordinate get_player_coordinates() const;
	virtual bool path_open() const;
	virtual bool move_player(char dir);

	virtual void generate_labyrinth() override;


	virtual void plant_trees() override;

	virtual bool valid_tree(const Tree& tree, const std::vector<Coordinate>& path);
	virtual bool is_tree(const Coordinate& coord);
	virtual bool is_on_path(const Coordinate& coord, const std::vector<Coordinate>& path);
	virtual void update_board();
	virtual void update_trees();
	virtual bool get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit); //bfs
	virtual bool player_on_exit() const;

private:
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start);
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start);
	void shuffle(std::vector<int>& visit_order);
	void generate_exits();
	void compare_exits();
	void generate_player();
	void starting_trees(); 
};

#endif // !TREEOCALYPSE_H
