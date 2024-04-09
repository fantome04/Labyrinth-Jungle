#ifndef JUNGLE_H
#define JUNGLE_H

#include "labyrinth.h"

class LabyrinthJungle : public Labyrinth
{
public:
	LabyrinthJungle();
	~LabyrinthJungle() = default;

	virtual void update(bool moved) override;
	virtual void update_trees() override;
	virtual void plant_trees() override;

	bool cut_tree(const Coordinate& coord, char dir);
	bool bfs_called() const;
	void bfs_called_change();

private:

	bool bfs_called_;
};

#endif // !JUNGLE_H
