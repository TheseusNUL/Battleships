#pragma once
#include "Vector2.h"
#include "Utils.h"
#include <string.h>

class Ship
{
public:

	enum ShipType
	{
		ST_NONE = 0,
		ST_AIRCRAFT_CARRIER,
		ST_BATTLESHIP,
		ST_CRUISER,
		ST_DESTROYER,
		ST_SUBMARINE
	};

	enum ShipOrientation
	{
		SO_HORIZONTAL = 0,
		SO_VERTICAL
	};

	void InitShip(int shipSize, ShipType shipType);

	ShipOrientation GetShipOrientation() const;
	ShipOrientation GetCurrentOrientation() const;

	ShipType GetShipType() const;
	std::string GetShipTypeName(ShipType shipType) const;
	int GetShipSize() const;
	Vector2 GetShipPosition() const;
	void SetShipPosition(Vector2 shipPos);

	void SetShipOrientation(ShipOrientation orientation);

private:
	int m_shipSize;

	ShipType m_shipType;
	ShipOrientation m_orientation;
	Vector2 m_shipPosition;
};

struct ShipPart
{
	Ship::ShipType partType;
	bool isHit;
};