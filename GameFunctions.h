#pragma once
#include<string>
using namespace std;

class GameFunctions
{
public:
	// Member Functions
	static void DisplayMessage(string message);
	static void DisplayMessage(string message, bool endline);
	static void DisplayArray(int array[], int size);
	static void DisplayRollResults(int result);

	static void ContinueMenu();
	static void ClearScreen();

	static int GetInteger();
	static string GetString();

	static int RollOneDice(int sidesOfDice);
	static int RollMultipleDice(int sidesOfDice, int numberOfDice, string getHighOrLow, bool choice);
};
