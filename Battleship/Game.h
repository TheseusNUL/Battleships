#pragma once
#include "Player.h"
#include "Console.h"
#include "Utils.h"

class Game
{
public:
	Game(Player& player1, Player& player2);
	bool PlayAgain();
	void PlayGame(Player& player1, Player& player2);
	void SetUpBoards(Player& player);
	bool GameOver(Player& player1, Player& player2) const;

	void DrawBoards(Player& player);
	void DrawSeparatorLine();
	void DrawColumnsRow();
	void DrawShipBoardRow(Player& player, int row);
	void DrawGuessBoardRow(Player& player, int row);

	Vector2 GetBoardPosition();
	Vector2 MapBoardPosition(char rowInput, int colInput);

	void SwitchPlayers(Player ** currentPlayer, Player ** otherPlayer);
	void DisplayWinner(Player& player1, Player& player2) const;

	//AI functions
	Vector2 GetRamdomPosition();
	Vector2 GetAIGuess(const Player& AI);
	void SetUpAIBoards(Player& player);

private:

	Player m_player1;
	Player m_player2;
};
