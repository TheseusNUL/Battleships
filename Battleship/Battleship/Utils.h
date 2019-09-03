#pragma once
#include <string>
#include <iostream>

enum CharacterCaseType
{
	CC_UPPER_CASE = 0,
	CC_LOWER_CASE,
	CC_EITHER
};

char GetCharInput(const char *prompt, const std::string& error, const char validInput[], int validInputLength, CharacterCaseType charCase);
char GetIntInput(const char *prompt, const std::string& error, const int validInput[], int validInputLength);

const std::string INPUT_ERROR_STRING = "Input error! Please try again.";
