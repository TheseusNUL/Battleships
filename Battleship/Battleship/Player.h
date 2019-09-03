#pragma once
#include <iostream>
#include <string>
#include "Ship.h"
#include "enums.h"

class Player
{
public:
	Player(const std::string& playerName);

	void ClearBoards();

	char GetShipRepresentation(int row, int col);
	char GetGuessRepresentation(int row, int col);
	Ship& GetShip(int index);
	std::string& GetPlayerName();

	bool IsPlacementValid(Ship& currentShip, const Vector2& shipPos, Ship::ShipOrientation orientation);
	bool isGuessValid(Vector2 guess);
	bool ShipSunk(Ship& ship);
	bool AreAllShipsSunk();

	void PlaceShip(Ship& currentShip, const Vector2& shipPos, Ship::ShipOrientation orientation);
	Ship::ShipType UpdateBoards(Player& otherPlayer, Vector2 guess);

private:
	std::string m_playerName;
	Ship m_ship[NUM_SHIPS];
	ShipPart m_shipboard[BOARD_SIZE][BOARD_SIZE];
	GuessType m_guessboard[BOARD_SIZE][BOARD_SIZE];
};
