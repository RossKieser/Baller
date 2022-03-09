#include <iostream>
#include "Team.h"
#include "GameSetupMenu.h"
#include "GameFunctions.h"
#include "GamePlay.h"

using namespace std;

//Member Functions

void GameFunctions::DisplayMessage(string message)
{
    cout << "     " << message << endl;
}

void GameFunctions::DisplayMessage(string message, bool sameLine)
{
    if (sameLine == true)
    {
        cout << "     " << message;
    }
    else
    {
        cout << "     " << message << endl;
    }
}

void GameFunctions::DisplayArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void GameFunctions::DisplayRollResults(int result)
{
    cout << "     " << "A " << result << " is rolled!" << endl;
    GameFunctions::ContinueMenu();
}


void GameFunctions::ContinueMenu()
{
    bool startGame = false;
    do
    {
        DisplayMessage("Press 1 to continue the game: ", true);
        int start = GetInteger();
        if (start == 1)
        {
            startGame = true;
        }
        else
        {
            DisplayMessage("Invalid! Try again!");
            startGame = false;
        }
    } while (!startGame);
}

void GameFunctions::ClearScreen()
{
    system("cls");
}


int GameFunctions::GetInteger()
{
    int number;

    do
    {
        cin >> number;

        if (cin.fail())
        {
            cin.clear();
            DisplayMessage("Invalid entry. Try again!");
            cin.ignore(1, '/n');
        }
        else
        {
            break;
        }

    } while (true);

    return number;

}

string GameFunctions::GetString()
{
    string word;
    cin >> word;
    return word;
}


int GameFunctions::RollOneDice(int sidesOfDice)
{
    int diceResult = (1 + rand() % sidesOfDice);
    return diceResult;
}

int GameFunctions::RollMultipleDice(int sidesOfDice, int numberOfDice, string getHighOrLow, bool choice)
{
    if (choice == false)
    {
        int highestDiceResult = 0;
        //choose a high number as the default for lowest result so that the first dice roll is less than it and gets registered
        int lowestDiceResult = 10000;
        for (int i = 0; i < numberOfDice; i++)
        {
            int diceResult = RollOneDice(sidesOfDice);
            cout << "     " << "Dice " << (i + 1) << ": " << diceResult << endl;
            if (diceResult > highestDiceResult)
            {
                highestDiceResult = diceResult;
            }
            if (diceResult < lowestDiceResult)
            {
                lowestDiceResult = diceResult;
            }
        }
        if (getHighOrLow == "High" || getHighOrLow == "high")
        {
            return highestDiceResult;
        }
        if (getHighOrLow == "Low" || getHighOrLow == "low")
        {
            return lowestDiceResult;
        }
    }
    else
    {
        int diceResults[5] = { 0, 0, 0, 0, 0 };

        for (int i = 0; i < numberOfDice; i++)
        {
            if (i == 0)
            {
                diceResults[0] = RollOneDice(sidesOfDice);
                cout << "     " << "Dice " << (i + 1) << ": " << diceResults[0] << endl;
            }
            if (i == 1)
            {
                diceResults[1] = RollOneDice(sidesOfDice);
                cout << "     " << "Dice " << (i + 1) << ": " << diceResults[1] << endl;
            }
            if (i == 2)
            {
                diceResults[2] = RollOneDice(sidesOfDice);
                cout << "     " << "Dice " << (i + 1) << ": " << diceResults[2] << endl;
            }
            if (i == 3)
            {
                diceResults[3] = RollOneDice(sidesOfDice);
                cout << "     " << "Dice " << (i + 1) << ": " << diceResults[3] << endl;
            }
            if (i == 4)
            {
                diceResults[4] = RollOneDice(sidesOfDice);
                cout << "     " << "Dice " << (i + 1) << ": " << diceResults[4] << endl;
            }
        }
        bool validResult = true;
        do
        {
            GameFunctions::DisplayMessage("Type the number (not the result) of the die you want to use: ", true);
            int diceNumber = GameFunctions::GetInteger();

            if (diceNumber == 1)
            {
                return diceResults[0];
            }
            else if (diceNumber == 2)
            {
                return diceResults[1];
            }
            else if (diceNumber == 3)
            {
                return diceResults[2];
            }
            else if (diceNumber == 4)
            {
                return diceResults[3];
            }
            else if (diceNumber == 5)
            {
                return diceResults[4];
            }
            else
            {
                validResult = false;
                GameFunctions::DisplayMessage("Invalid input! Try Again!");
            }
        } while (!validResult);
    }
}
