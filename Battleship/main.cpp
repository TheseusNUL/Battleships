#include <iostream>
#include "Ship.h"
#include "Player.h"
#include "Game.h"

/* -----------------------------------------------------------------------***RULES***--------------------------------------------------------------------------------------------------
Game: Battleship
The game is played on four 10x10 grids by two players, with each player having two grids each.
The rows of the grid will be labeled sequentially from A to J and the columns labeled sequentially from 1 to 10.
Each player will have to arrange their individual ships on their respected grid before the start of the game. Each ship occupies a number of consecutive squares on the grid, arranged
either horizontally or vertically. The number of squares for each ship is determined by the type of ship. The ships CANNOT overlap.

The ships are as follows:

Ship type				Size
----------------------+-----------
Aircraft carrier      |		5
Battleship			  |		4
Cruiser				  |		3
Destroyer			  |		3
Submarine			  |		2

After both players have positioned their ships, the game begins and proceeds in a series of rounds. In each round, each player take a turn to select a target square on the opponents
grid which is to be shot at. The game will then indicate whether or not the square is occupied by a ship or not. A mark will be placed on the board to indicate the result of the shot.
If the shot was a success then the attacked players board will be marked with the appropriate indicator to show that the ship was struck.  That will end the turn.

When all grids a ship occupies are hit, the ship is sunk and the game will output information of what ship was sunk. If all of a players ships has been sunk, then the player with the
remaining ship wins the game.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

int main()
{
	Player player1("player1");
	Player player2("player2");

	Game game(player1, player2);

	do 
	{
		game.PlayGame(player1, player2);

	} while (game.PlayAgain());

	return 0;
}