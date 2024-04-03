#ifndef GAME_H
#define GAME_H

#include "labyrinth.h"
#include "coordinate.h"
#include "labyrinthtreeocalypse.h"
#include "labyrinthjungle.h"

enum class GameMode
{
	TREEOCALYPSE,
	WTTJ
};

class Game
{
public:
	Game();

	void play();

	~Game();

private:

	void prologue(); //start menu
	void epilogue_win(); //game over screen
	void epilogue_lose(); //game over screen
	void treeocalypse_game_loop();
	void wttj_game_loop();
	void treeocalypse_update();
	char read_input();

	bool game_over_;
	bool win;
	GameMode mode_;
	Labyrinth* maze_;
	

};

#endif