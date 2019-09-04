#include "Player.h"

Player::Player(const std::string& playerName)
	:m_playerName(playerName)
{	
	m_ship[0].InitShip(AIRCRAFT_CARRIER_SIZE, Ship::ST_AIRCRAFT_CARRIER);
	m_ship[1].InitShip(BATTLESHIP_SIZE, Ship::ST_BATTLESHIP);
	m_ship[2].InitShip(CRUISER_SIZE, Ship::ST_CRUISER);
	m_ship[3].InitShip(DESTROYER_SIZE, Ship::ST_DESTROYER);
	m_ship[4].InitShip(SUBMARINE_SIZE, Ship::ST_SUBMARINE);
}

void Player::ClearBoards()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			m_guessboard[i][j] = GT_NONE;
			m_shipboard[i][j].partType = Ship::ST_NONE;
			m_shipboard[i][j].isHit = false;
		}
	}
}

char Player::GetShipRepresentation(int row, int col)
{
	if (m_shipboard[row][col].isHit)
	{
		return '*';
	}

	switch (m_shipboard[row][col].partType)
	{
	case Ship::ST_AIRCRAFT_CARRIER: return 'A';
		break;
	case Ship::ST_BATTLESHIP: return 'B';
		break;
	case Ship::ST_CRUISER: return 'C';
		break;
	case Ship::ST_DESTROYER: return 'D';
		break;
	case Ship::ST_SUBMARINE: return 'S';
		break;
	default: return ' ';
		break;
	};
}

char Player::GetGuessRepresentation(int row, int col)
{
	switch (m_guessboard[row][col])
	{
	case GT_HIT:
		return '*';
		break;
	case GT_MISSED:
		return 'o';
	default:
		return ' ';
	}
		
}

Ship& Player::GetShip(int index)
{
	return m_ship[index];
}

std::string& Player::GetPlayerName()
{
	return m_playerName;
}

Player::PlayerType Player::GetPlayerType()
{
	return m_playerType;
}

Player::PlayerType Player::SetGameMode()
{
	const int validInputs[2] = { 1, 2 };

	int input = GetIntInput("Select your game mode:\n1. Single-Player\n2. Multi-Player\n", INPUT_ERROR_STRING, validInputs, 2);

	switch (input)
	{
	case 1: return PT_AI;
		break;
	case 2: return PT_HUMAN;
		break;
	}
}

void Player::SetPlayerType(PlayerType playerType)
{
	m_playerType = playerType;
}

bool Player::IsPlacementValid(Ship& currentShip, const Vector2& shipPos, Ship::ShipOrientation orientation)
{
	switch (orientation)
	{
	case Ship::SO_HORIZONTAL:
	{
		for (int i = shipPos.m_col; i < (shipPos.m_col + currentShip.GetShipSize()); i++)
		{
			if (m_shipboard[shipPos.m_row][i].partType != Ship::ShipType::ST_NONE || i >= BOARD_SIZE)
			{
				return false;
			}
		}

		break;
	}
	case Ship::SO_VERTICAL:
	{
		for (int i = shipPos.m_row; i < (shipPos.m_row + currentShip.GetShipSize()); i++)
		{
			if (m_shipboard[i][shipPos.m_col].partType != Ship::ShipType::ST_NONE || i >= BOARD_SIZE)
			{
				return false;
			}
		}
		break;
	}

		return true;
	}
}

bool Player::isGuessValid(Vector2 guess)
{
	//If current player has not guessed at this vector then guess is valid. If so they have already attempted to guess here.
	if (m_guessboard[guess.m_row][guess.m_col] == GT_NONE)
		return true;
	else
		return false;
}

bool Player::ShipSunk(Ship& ship)
{
	if (ship.GetCurrentOrientation() == Ship::SO_HORIZONTAL)
	{
		for (int i = ship.GetShipPosition().m_col; i < (ship.GetShipPosition().m_col + ship.GetShipSize()); i++)
		{
			//If any ship part is not hit the ship cannot be sunk
			if (!m_shipboard[ship.GetShipPosition().m_row][i].isHit)
				return false;
		}
	}
	else
	{
		for (int i = ship.GetShipPosition().m_row; i < (ship.GetShipPosition().m_row + ship.GetShipSize()); i++)
		{
			//If any ship part is not hit the ship cannot be sunk
			if (!m_shipboard[i][ship.GetShipPosition().m_col].isHit)
				return false;
		}
	}

	//if all parts of a ship are hit then ship is sunk
	return true;
}

bool Player::AreAllShipsSunk()
{
	for (int i = 0; i < NUM_SHIPS; i++)
	{
		if (!ShipSunk(m_ship[i]))
			return false;
	}

	return true;
}

void Player::PlaceShip(Ship& currentShip, const Vector2& shipPos, Ship::ShipOrientation orientation)
{
	currentShip.SetShipPosition(Vector2(shipPos.m_row, shipPos.m_col));
	currentShip.SetShipOrientation(orientation);

	switch (orientation)
	{
	case Ship::SO_HORIZONTAL:
	{
		for (int i = shipPos.m_col; i < (shipPos.m_col + currentShip.GetShipSize()); i++)
		{
			m_shipboard[shipPos.m_row][i].partType = currentShip.GetShipType();
			m_shipboard[shipPos.m_row][i].isHit = false;
		}
		break;
	}
	case Ship::SO_VERTICAL:
	{
		for (int i = shipPos.m_row; i < (shipPos.m_row + currentShip.GetShipSize()); i++)
		{
			m_shipboard[i][shipPos.m_col].partType = currentShip.GetShipType();
			m_shipboard[i][shipPos.m_col].isHit = false;
		}
		break;
	}
	}
}

Ship::ShipType Player::UpdateBoards(Player& otherPlayer, Vector2 guess)
{
	if (otherPlayer.m_shipboard[guess.m_row][guess.m_col].partType != Ship::ST_NONE)
	{
		//hit
		m_guessboard[guess.m_row][guess.m_col] = GT_HIT;
		otherPlayer.m_shipboard[guess.m_row][guess.m_col].isHit = true;
	}
	else
	{
		//miss
		m_guessboard[guess.m_row][guess.m_col] = GT_MISSED;
	}

	return otherPlayer.m_shipboard[guess.m_row][guess.m_col].partType;
}
