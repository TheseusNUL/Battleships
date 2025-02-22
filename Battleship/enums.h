#pragma once

enum
{
	AIRCRAFT_CARRIER_SIZE = 5,
	BATTLESHIP_SIZE = 4,
	CRUISER_SIZE = 3,
	DESTROYER_SIZE = 3,
	SUBMARINE_SIZE = 2,

	BOARD_SIZE = 10,
	NUM_SHIPS = 5,
	MAX_SHIP_SIZE = AIRCRAFT_CARRIER_SIZE
};

enum GuessType
{
	GT_NONE = 0,
	GT_MISSED,
	GT_HIT
};