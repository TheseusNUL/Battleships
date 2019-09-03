#include "Utils.h"

char GetCharInput(const char *prompt, const std::string& error, const char validInput[], int validInputLength, CharacterCaseType charCase)
{
	/*--------------------------------------------------------------------------------------------------------
		std::cin.fail() detects whether the value entered fits the value defined in the variable.
		But if std::cin.fail() is true, it means that
		a) the entered value does not fit the variable
		b) the variable will not be affected
		c) the instream is still broken
		d) the entered value is still in the buffer and will be used for the next "std::cin >> variable"statement.

		Hence you have to do the following :
		a) repair the instream via std::cin.clear();
		b) clear the buffer with std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	----------------------------------------------------------------------------------------------------------*/

	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			failure = true;
		}
		else
		{
			std::cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input))
			{
				if (charCase == CC_UPPER_CASE)
				{
					input = toupper(input);
				}
				else if (charCase == CC_LOWER_CASE)
				{
					input = tolower(input);
				}

				for (int i = 0; i < validInputLength; i++)
				{
					if (input == validInput[i])
					{
						return input;
					}
				}
			}

			std::cout << error << std::endl;
			failure = true;

		}

	} while (failure);

	return input;
}

char GetIntInput(const char *prompt, const std::string& error, const int validInput[], int validInputLength)
{
	int input;
	bool inputFailure;

	const int IGNORE_CHARS = 256;
	do
	{

		inputFailure = false;

		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			inputFailure = true;
		}
		else
		{
			for (int i = 0; validInputLength; i++)
			{
				if (input == validInput[i])
				{
					return input;
				}
			}


			std::cout << error << std::endl;
			inputFailure = true;
		}


	} while (inputFailure);

	return -1;
}