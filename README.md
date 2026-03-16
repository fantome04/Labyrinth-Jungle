# Labyrinth Console Game

A console-based **Labyrinth game** implemented using ASCII graphics.
The player must navigate a **20×20 labyrinth** and reach one of the exits while avoiding obstacles.

## Board Representation

The labyrinth is displayed using ASCII characters:

* `.` — empty cell (walkable)
* `#` — tree (obstacle)
* `1–10` — planted cell countdown (Treeocalypse mode)

The board size is **20 × 20**, and the labyrinth contains **one or two exits**.

## Player Movement

Each turn the player can move to one of the **four neighboring cells**:

* Up
* Down
* Left
* Right

The player may move only to **empty cells** or **planted cells**.

---

# Game Modes

## Treeocalypse

After each player move:

* **Three random empty cells** become **planted**.
* Each planted cell receives a **countdown from 1 to 10**.
* The countdown decreases after every move.
* When the countdown reaches **0**, the cell becomes a **tree (`#`)**.

The player can step on planted cells until they become trees.

New planted cells are added **only if the labyrinth remains solvable**.
If adding a planted cell would make the labyrinth unwinnable, the planting step is skipped.

---

## Welcome to the Jungle

The labyrinth initially contains **many trees**, making it impossible to escape normally.

The player can **cut up to 3 trees** during the game.
To successfully escape, the player must **cut at least 2 trees**.

---

# Game Validity

Every generated game must satisfy the following conditions:

* The labyrinth is **solvable**.
* The **shortest solution requires at least 5 moves**.
* In **Welcome to the Jungle mode**, the player must **cut at least 2 trees** to escape.

A **modified wave (BFS) algorithm** is used for solvability checks and planted cell placement.

---

# Naming Conventions

The project follows consistent naming conventions.

## Classes

* Class names: **PascalCase**
* Constructors: **PascalCase**

Example:

```cpp
class HumanPlayer;
class Labyrinth;
```

## Methods

* Method names: **snake_case**

Example:

```cpp
move_player()
generate_labyrinth()
check_win_condition()
```

## Class Members

* Member variables: **snake_case_** (trailing underscore)

Example:

```cpp
int player_position_;
int moves_count_;
```

## Constants

* Constant names: **ALL_CAPS**

Example:

```cpp
MAX_LABYRINTH_SIZE
MAX_TREE_CUTS
```

## Files

* Source files: **flatcase**
* Header files: **flatcase** (same name as source file)

Example:

```
game.cpp
game.h
labyrinth.cpp
labyrinth.h
```

## Include Guards

Include guards follow the pattern:

```cpp
#ifndef LABYRINTH_H
#define LABYRINTH_H

// declarations

#endif
```
