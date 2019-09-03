#include "Ship.h"
#include <string>

void Ship::InitShip(int shipSize, ShipType shipType)
{
	m_shipType = shipType;
	m_shipSize = shipSize;
	m_shipPosition.m_row = 0;
	m_shipPosition.m_col = 0;
	m_orientation = SO_HORIZONTAL;
}

Ship::ShipType Ship::GetShipType() const
{
	return m_shipType;
}

Ship::ShipOrientation Ship::GetShipOrientation() const
{
	const char validInput[2] = { 'H', 'V' };

	char input = GetCharInput("Please choose (H) Horizontal or (V) Vertical orientation ", INPUT_ERROR_STRING, validInput, 2, CC_UPPER_CASE);

	if (input == validInput[0])
	{
		return SO_HORIZONTAL;
	}
	else
	{
		return SO_VERTICAL;
	}
}

Ship::ShipOrientation Ship::GetCurrentOrientation() const
{
	return m_orientation;
}

std::string Ship::GetShipTypeName(Ship::ShipType shipType) const
{
	switch (shipType)
	{
	case ST_AIRCRAFT_CARRIER:
		return "Aircraft Carrier";
		break;
	case ST_BATTLESHIP:
		return "Battleship";
		break;
	case ST_CRUISER:
		return "Cruiser";
		break;
	case ST_DESTROYER:
		return "Destroyer";
		break;
	case ST_SUBMARINE:
		return "Submarine";
		break;
	default:
		return "None";
	}
}

int Ship::GetShipSize() const
{
	return m_shipSize;
}

Vector2 Ship::GetShipPosition() const
{
	return m_shipPosition;
}


void Ship::SetShipPosition(Vector2 shipPos)
{
	m_shipPosition.m_row = shipPos.m_row;
	m_shipPosition.m_col = shipPos.m_col;
}

void Ship::SetShipOrientation(ShipOrientation orientation)
{
	m_orientation = orientation;
}
