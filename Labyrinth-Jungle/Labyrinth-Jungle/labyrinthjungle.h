#ifndef JUNGLE_H
#define JUNGLE

#include "labyrinth.h"

class LabyrinthJungle : public Labyrinth
{
public:
	LabyrinthJungle();
	~LabyrinthJungle() = default;

	virtual void generate_labyrinth() override;


	virtual void plant_trees() override;

};
#endif // !JUNGLE_H
