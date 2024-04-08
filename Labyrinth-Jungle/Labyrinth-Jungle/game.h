#ifndef GAME_H
#define GAME_H

#include "labyrinth.h"
#include "coordinate.h"
#include "labyrinthtreeocalypse.h"
#include "labyrinthjungle.h"
#include "humanplayer.h"
#include "player.h"

enum class GameMode
{
	TREEOCALYPSE,
	JUNGLE
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
	void game_loop();
	void treeocalypse_update();
	void jungle_update();
	char read_input();

	void generate_player();
	bool player_on_exit() const;

	bool game_over_;
	bool win_;
	GameMode mode_;
	Labyrinth* maze_;
	Player* human_;
	

};

#endif