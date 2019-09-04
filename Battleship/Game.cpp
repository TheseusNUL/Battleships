#include "Game.h"
#include <cstdlib>
#include <ctime>
#include "enums.h"

Game::Game(Player& player1, Player& player2)
	: m_player1(player1)
	, m_player2(player2)
	, m_prevGuessType(GT_MISSED)
	, m_prevGuessPos(0, 0)
{
	srand(time(NULL));

	PlayGame(player1, player2);
}

bool Game::PlayAgain()
{
	char input;

	const char validInput[2] = { 'y', 'n' };

	input = GetCharInput("Would you like to play again? (y/n): ", INPUT_ERROR_STRING, validInput, 2, CC_LOWER_CASE);

	return input == 'y';

}

void Game::PlayGame(Player& player1, Player& player2)
{
	system("cls");

	player1.SetPlayerType(Player::PT_HUMAN);
	player2.SetPlayerType(player2.SetGameMode());

	SetUpBoards(player1);
	SetUpBoards(player2);

	Player* pCurrentPlayer = &player1;
	Player* pOtherPlayer = &player2;

	Vector2 guess;

	do 
	{
		if(pCurrentPlayer->GetPlayerType() == Player::PT_HUMAN)
		DrawBoards(*pCurrentPlayer);

		bool isGuessValid;

		do
		{
			switch (pCurrentPlayer->GetPlayerType())
			{
			case Player::PT_HUMAN:
			{
				std::cout << pCurrentPlayer->GetPlayerName() << " please make a guess" << std::endl;
				guess = GetBoardPosition();
				break;
			}
			case Player::PT_AI:
			{
				guess = GetAIGuess(*pCurrentPlayer);
				m_prevGuessPos = guess;
				break;
			}
			}
			
			isGuessValid = pCurrentPlayer->isGuessValid(guess);

			if (!isGuessValid && pCurrentPlayer->GetPlayerType() == Player::PT_HUMAN)
			{
				std::cout << "This was not a valid guess! Please try again." << std::endl;
			}
		} while (!isGuessValid);

		Ship::ShipType type = pCurrentPlayer->UpdateBoards(*pOtherPlayer, guess);

		if (pCurrentPlayer->GetPlayerType() == Player::PT_AI)
			m_prevGuessType = pCurrentPlayer->GetGuessType(*pOtherPlayer, guess);

		switch (pCurrentPlayer->GetPlayerType())
		{
		case Player::PT_HUMAN:
		{
			DrawBoards(*pCurrentPlayer);
			break;
		}
		case Player::PT_AI:
		{
			DrawBoards(*pOtherPlayer);
			std::cout << pCurrentPlayer->GetPlayerName() << " chose tile " << char(guess.m_row + 'A') << guess.m_col + 1 << std::endl;
		}
		}

		/* -------------------------------------------------------------------------------
			index for type is type-1 due to enum of ships types being one out of sync with 
			ships initialization with player ships member.
		--------------------------------------------------------------------------------*/

		if (type != Ship::ST_NONE && pOtherPlayer->ShipSunk(pOtherPlayer->GetShip(type - 1)))
		{
			std::cout << "You sunk " << pOtherPlayer->GetPlayerName() << "'s " << pOtherPlayer->GetShip(type-1).GetShipTypeName(type) << "!" << std::endl; 
		}

		system("pause");

		SwitchPlayers(&pCurrentPlayer, &pOtherPlayer);

	} while (!GameOver(player1, player2));

	DisplayWinner(player1, player2);
}

void Game::SetUpBoards(Player& player)
{
	player.ClearBoards();

	if (player.GetPlayerType() == Player::PlayerType::PT_AI)
	{
		SetUpAIBoards(player);
		return;
	}

	for (int i = 0; i < NUM_SHIPS; i++)
	{
		DrawBoards(player);

		Ship& currentShip = player.GetShip(i);

		Vector2 shipPos;
		Ship::ShipOrientation shipOrentation;

		bool isPlacementValid = false;

		do
		{
			std::cout << player.GetPlayerName() << " set the position and orientation for your " << currentShip.GetShipTypeName(currentShip.GetShipType()) << std::endl;

			shipPos = GetBoardPosition();
			shipOrentation = currentShip.GetShipOrientation();

			isPlacementValid = player.IsPlacementValid(currentShip, shipPos, shipOrentation);

			if (!isPlacementValid)
			{
				std::cout << "Not a valid placement. Please try again." << std::endl;
				system("pause");
			}

		} while (!isPlacementValid);

		player.PlaceShip(currentShip, shipPos, shipOrentation);
	}

	DrawBoards(player);
	system("pause");

}


bool Game::GameOver(Player& player1, Player& player2) const
{
	if (player1.AreAllShipsSunk() || player2.AreAllShipsSunk())
		return true;
	else
		return false;
}

void Game::DrawBoards(Player& player)
{
	system("cls");

	DrawColumnsRow();

	DrawColumnsRow();

	std::cout << std::endl;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		DrawSeparatorLine();

		std::cout << " ";

		DrawSeparatorLine();

		std::cout << std::endl;

		DrawShipBoardRow(player, i);

		std::cout << " ";

		DrawGuessBoardRow(player, i);

		std::cout << std::endl;
	}

	DrawSeparatorLine();

	std::cout << " ";

	DrawSeparatorLine();

	std::cout << std::endl;
}

void Game::DrawSeparatorLine()
{
	std::cout << " ";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << "+---";
	}

	std::cout << "+";
}

void Game::DrawColumnsRow()
{
	std::cout << "  ";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		int columnName = i + 1;

		std::cout << " " << columnName << "  ";
	}
}

void Game::DrawShipBoardRow(Player& player, int row)
{
	char rowName = row + 'A';
	std::cout << rowName << "|";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << " " << player.GetShipRepresentation(row, i) << " |";
	}
}

void Game::DrawGuessBoardRow(Player& player, int row)
{
	char rowName = row + 'A';
	std::cout << rowName << "|";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << " " << player.GetGuessRepresentation(row, i) << " |";
	}
}

Vector2 Game::GetBoardPosition()
{
	char rowInput;
	int colInput;

	const char validRowInputs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	const int validColumnInputs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	rowInput = GetCharInput("Please input a row (A - J): ", INPUT_ERROR_STRING, validRowInputs, BOARD_SIZE, CC_UPPER_CASE);
	colInput = GetIntInput("Please input a column (1 - 10): ", INPUT_ERROR_STRING, validColumnInputs, BOARD_SIZE);

	return MapBoardPosition(rowInput, colInput);
}

Vector2 Game::MapBoardPosition(char rowInput, int colInput)
{
	int row = rowInput - 'A';
	int col = colInput - 1;

	Vector2 boardPos;

	boardPos.m_row = row;
	boardPos.m_col = col;

	return boardPos;
}

void Game::SwitchPlayers(Player ** currentPlayer, Player ** otherPlayer)
{
	/*----------------------------------------------------------------
						 ------->	player 1 ---
						|						|
		current player - (switch ptr)			 -------> Player
												|
									player 2 ---
	----------------------------------------------------------------*/

	Player * temp = *currentPlayer;
	*currentPlayer = *otherPlayer;
	*otherPlayer = temp;
}

void Game::DisplayWinner(Player& player1, Player& player2) const
{
	if (player1.AreAllShipsSunk())
		std::cout << player2.GetPlayerName() << " is the winner. Congratulations!" << std::endl;
	else
		std::cout << player1.GetPlayerName() << " is the winner. Congratulations!" << std::endl;
}

Vector2 Game::GetRamdomPosition()
{
	Vector2 guess;

	guess.m_row = rand() % BOARD_SIZE;
	guess.m_col = rand() % BOARD_SIZE;

	return guess;
}

Vector2 Game::GetAIGuess(Player& ai)
{
	Vector2 selectionRow[4] = { Vector2(m_prevGuessPos.m_row + 1, m_prevGuessPos.m_col), Vector2(m_prevGuessPos.m_row - 1, m_prevGuessPos.m_col),
		Vector2(m_prevGuessPos.m_row, m_prevGuessPos.m_col + 1), Vector2(m_prevGuessPos.m_row, m_prevGuessPos.m_col - 1) };


	Vector2 nextPos;
	int randomIndex;

	switch (m_prevGuessType)
	{
	case GT_HIT:
	{
		randomIndex = rand() % 4;
		nextPos = selectionRow[randomIndex];

		if (ai.isGuessValid(nextPos))
		{
			return nextPos;
		}
		else
		{
			return GetRamdomPosition();
		}

		break;
	}
	case GT_MISSED:
	{
		return GetRamdomPosition();
	}

	}

}

void Game::SetUpAIBoards(Player& player)
{
	Vector2 shipPos;
	Ship::ShipOrientation orientation;

	for (int i = 0; i < NUM_SHIPS; i++)
	{
		Ship& currentShip = player.GetShip(i);
		do
		{
			shipPos = GetRamdomPosition();
			orientation = Ship::ShipOrientation(rand() % 2);

		} while (!player.IsPlacementValid(currentShip, shipPos, orientation));

		player.PlaceShip(currentShip, shipPos, orientation);
	}

}

