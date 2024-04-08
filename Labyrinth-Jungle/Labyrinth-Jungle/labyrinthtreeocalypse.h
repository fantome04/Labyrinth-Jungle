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
	
};

#endif // !TREEOCALYPSE_H
