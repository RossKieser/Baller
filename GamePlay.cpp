#include <iostream>
#include "Team.h"
#include "GameSetupMenu.h"
#include "GameFunctions.h"
#include "GamePlay.h"

using namespace std;

// Member Functions


void GamePlay::PlayBasketball()
{
    Team::DisplayBothTeamInfo(Player1Team, Player2Team);

    GameFunctions::ContinueMenu();
    GameFunctions::ClearScreen();

    DetermineBothTargetScores(Player1Team, Player2Team);

    GameFunctions::ContinueMenu();
    GameFunctions::ClearScreen();

    GameFunctions::DisplayMessage("Time for the tipoff!");
    Tipoff();

    bool didPlayer1WinTipoff = Player1Team.GetPossession();
    if (didPlayer1WinTipoff == true)
    {
        cout << "     " << "The " << Player1Team.GetTeamName() << " win the tipoff!" << endl;
    }
    else
    {
        cout << "     " << "The " << Player2Team.GetTeamName() << " win the tipoff!" << endl;
    }
    GameFunctions::ContinueMenu();
    GameFunctions::ClearScreen();

    PlayBall();

    // int test = RollMultipleDice(20, 5, "High", true);
    // cout << "Your roll was: " << test << endl;
}

void GamePlay::DetermineBothTargetScores(Team& team1, Team& team2)
{
    GameFunctions::DisplayMessage("It's gameday! Welcome to the pregame show!");
    GameFunctions::DisplayMessage("Let's take a look at the vegas odds...");
    cout << endl;

    DetermineIndividualTargetScores(team1);
    DetermineIndividualTargetScores(team2);
}

void GamePlay::DetermineIndividualTargetScores(Team& team)
{
    static int DiceSides[5] = { 15,12,10,8,6 };
    int teamStrength = team.GetStat(ES_TeamStrength);
    int teamConsistency = team.GetStat(ES_TeamConsistency);
    //we subtract one because the array starts at 0, and team strength starts at 1, so 1 = 0 in the array
    int numSidedDice = DiceSides[teamStrength - 1];

    int spread = GameFunctions::RollMultipleDice(numSidedDice, teamConsistency, "Low", false);
    team.AddToTargetScore(spread);

    string teamName = team.GetTeamName();
    int targetScore = team.GetTargetScore();

    cout << endl;
    cout << "     " << teamName << " target score is: " << targetScore << endl;
    cout << "     " << "Reach " << targetScore << " to win the game!" << endl;

    cout << endl;
}

void GamePlay::Tipoff()
{
    bool tie = true;
    do
    {
        int player1Roll = GameFunctions::RollOneDice(20);
        int player2Roll = GameFunctions::RollOneDice(20);

        if (player1Roll > player2Roll)
        {
            Player1Team.SetPossession(true);
            Player2Team.SetPossession(false);
            tie = false;
        }
        else if (player1Roll < player2Roll)
        {
            Player1Team.SetPossession(false);
            Player2Team.SetPossession(true);
            tie = false;
        }
    } while (tie);
}

void GamePlay::PlayBall()
{
    Player1Team.SetTotalDiceValue(0);
    Player2Team.SetTotalDiceValue(0);
    while ((Player1Team.GetTargetScore() > Player1Team.GetScore()) && (Player2Team.GetTargetScore() > Player2Team.GetScore()))
    {
        DesignateODRolls();
        Team* possessionWinner = CompareODRolls();
        ResolvePossession(possessionWinner);
    }
    if (Player1Team.GetScore() >= Player1Team.GetTargetScore() || Player2Team.GetScore() >= Player2Team.GetTargetScore())
    {
        GameOver();
    }
}

void GamePlay::GameOver()
{
    if (Player1Team.GetScore() >= Player1Team.GetTargetScore())
    {
        cout << endl;
        cout << "     " << "THE " << Player1Team.GetTeamName() << " WIN THE GAME!!!" << endl;
        cout << "     " << "Impressive win, coach " << Player1Team.GetCoachName() << "!" << endl;
        GameFunctions::DisplayMessage("What a hard fought game! See you next time!");
    }
    if (Player2Team.GetScore() >= Player2Team.GetTargetScore())
    {
        cout << endl;
        cout << "     " << "THE " << Player2Team.GetTeamName() << " WIN THE GAME!!!" << endl;
        cout << "     " << "Impressive win, coach " << Player2Team.GetCoachName() << "!" << endl;
        GameFunctions::DisplayMessage("What a hard fought game! See you next time!");
    }
}


void GamePlay::SetODTeam()
{
    offensiveTeam = nullptr;
    defensiveTeam = nullptr;

    if (Player1Team.GetPossession())
    {
        offensiveTeam = &Player1Team;
        defensiveTeam = &Player2Team;
    }
    else
    {
        offensiveTeam = &Player2Team;
        defensiveTeam = &Player1Team;
    }
}

void GamePlay::SetActiveTeam()
{
    activeTeam = nullptr;
    inactiveTeam = nullptr;

    if (Player1Team.GetPossession())
    {
        activeTeam = &Player1Team;
        inactiveTeam = &Player2Team;
    }
    else if (Player2Team.GetPossession())
    {
        activeTeam = &Player2Team;
        inactiveTeam = &Player1Team;
    }
}

void GamePlay::SwitchActiveTeam()
{
    if (activeTeam == &Player1Team)
    {
        activeTeam = &Player2Team;
        inactiveTeam = &Player1Team;
    }
    else
    {
        activeTeam = &Player1Team;
        inactiveTeam = &Player2Team;
    }
}

string GamePlay::GetTeamNameFromPointer(Team* pointerName)
{
    if (pointerName == &Player1Team)
    {
        return Player1Team.GetTeamName();
    }
    if (pointerName == &Player2Team)
    {
        return Player2Team.GetTeamName();
    }
}

void GamePlay::DisplayODTeam()
{
    if (Player1Team.GetPossession())
    {
        cout << "     " << Player1Team.GetTeamName() << " are on Offense." << endl;
        cout << "     " << Player2Team.GetTeamName() << " are on Defense." << endl;
    }
    else
    {
        cout << "     " << Player2Team.GetTeamName() << " are on Offense." << endl;
        cout << "     " << Player1Team.GetTeamName() << " are on Defense." << endl;
    }
}



void GamePlay::DisplayScore()
{
    cout << endl;
    GameFunctions::DisplayMessage("The score is: ");
    cout << "     " << Player1Team.GetTeamName() << ": " << Player1Team.GetScore() << endl;
    cout << "     " << Player2Team.GetTeamName() << ": " << Player2Team.GetScore() << endl;
    GameFunctions::ContinueMenu();
}


void GamePlay::DesignateODRolls()
{
    SetODTeam();
    cout << endl;
    DisplayODTeam();
    SetActiveTeam();
    for (int i = 0; i < 2; i++)
    {
        cout << endl;
        cout << "     " << "The " << activeTeam->GetTeamName() << " are ready for action!" << endl;
        bool choseAdd = false;
        bool choseSubtract = false;
        bool choseAddToOpponent = false;
        bool validInput = false;
        int choice = 0;

        //check if team is on offense
        const bool isOffence = offensiveTeam == activeTeam;
        const int statToUse = isOffence ? activeTeam->GetStat(ES_OffensiveSkill) : activeTeam->GetStat(ES_DefensiveSkill);

        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            cout << "     " << "Lets see if the " << activeTeam->GetTeamName() << " can make a play!" << endl;
            int roll = GameFunctions::RollMultipleDice(30, statToUse, "High", true);
            do
            {
                cout << endl;
                cout << "     " << "Choose where you want your roll of " << roll << " to go (must choose each option once each possession):" << endl;
                if (!choseAdd)
                {
                    GameFunctions::DisplayMessage("1) Add to your total");
                }
                if (!choseSubtract)
                {
                    GameFunctions::DisplayMessage("2) Subtract from your total");
                }
                if (!choseAddToOpponent)
                {
                    GameFunctions::DisplayMessage("3) Add to opponents total (Difference from 15 (x2))");
                }

                choice = GameFunctions::GetInteger();
                if ((choice == EOD_Add) || (choice == EOD_Subtract) || (choice == EOD_AddToOpponent))
                {
                    if (choseAdd == true && choice == EOD_Add)
                    {
                        GameFunctions::DisplayMessage("You already chose this option! Choose another option");
                        validInput = false;
                    }
                    else if (choseSubtract == true && choice == EOD_Subtract)
                    {
                        GameFunctions::DisplayMessage("You already chose this option! Choose another option");
                        validInput = false;
                    }
                    else if (choseAddToOpponent == true && choice == EOD_AddToOpponent)
                    {
                        GameFunctions::DisplayMessage("You already chose this option! Choose another option");
                        validInput = false;
                    }
                    else if (choseAdd == false && choice == EOD_Add)
                    {
                        choseAdd = true;
                        validInput = true;
                    }
                    else if (choseSubtract == false && choice == EOD_Subtract)
                    {
                        choseSubtract = true;
                        validInput = true;
                    }
                    else if (choseAddToOpponent == false && choice == EOD_AddToOpponent)
                    {
                        choseAddToOpponent = true;
                        validInput = true;
                    }
                }
                else
                {
                    GameFunctions::DisplayMessage("Invalid input! Try again!");
                    validInput = false;
                }
            } while (!validInput);
            if (choice == EOD_Add)
            {
                choseAdd = true;
                activeTeam->AddToTotalDiceValue(roll);
            }
            else if (choice == EOD_Subtract)
            {
                choseSubtract = true;
                activeTeam->AddToTotalDiceValue(-(roll));
            }
            else if (choice == EOD_AddToOpponent)
            {
                choseAddToOpponent = true;
                if ((roll - 15) > 0)
                {
                    inactiveTeam->AddToTotalDiceValue((roll - 15) * 2);
                }
                else if ((roll - 15) < 0)
                {
                    inactiveTeam->AddToTotalDiceValue(-((roll - 15) * 2));
                }
                else if ((roll - 15) == 0)
                {
                    inactiveTeam->AddToTotalDiceValue(0);
                }
            }
            GameFunctions::ClearScreen();
            cout << "     " << activeTeam->GetTeamName() << " total dice value is: " << activeTeam->GetTotalDiceValue() << endl;
            cout << "     " << inactiveTeam->GetTeamName() << " total dice value is: " << inactiveTeam->GetTotalDiceValue() << endl;

        }
        SwitchActiveTeam();
    }
}

Team* GamePlay::CompareODRolls()
{
    if (Player1Team.GetTotalDiceValue() == Player2Team.GetTotalDiceValue())
    {
        Team* strongerTeam = Team::CompareHighestStat(Player1Team, Player2Team, ES_TeamStrength);
        Team::ResetDiceTotal(Player1Team, Player2Team, 0);
        if (strongerTeam == nullptr)
        {
            cout << endl;
            GameFunctions::DisplayMessage("It's a tie but...");
            cout << "     " << "The home team " << Player1Team.GetTeamName() << " made a big play!" << endl;
            return &Player1Team;
        }
        else
        {
            cout << endl;
            GameFunctions::DisplayMessage("It's a tie but...");
            cout << "     " << "The strength of the " << GetTeamNameFromPointer(strongerTeam) << " made the difference with that big play!" << endl;
            return strongerTeam;
        }
    }
    else
    {
        Team* winningTeam = &Player2Team;
        if (Player1Team.GetTotalDiceValue() > Player2Team.GetTotalDiceValue())
        {
            winningTeam = &Player1Team;
        }
        cout << endl;
        cout << "     " << "The " << GetTeamNameFromPointer(winningTeam) << " have a higher total!" << endl;
        cout << "     " << "The " << GetTeamNameFromPointer(winningTeam) << " made a big play!" << endl;
        Team::ResetDiceTotal(Player1Team, Player2Team, 0);
        return winningTeam;
    }
}

void GamePlay::ResolvePossession(Team* possessionWinner)
{
    SetODTeam();
    cout << endl;
    DisplayODTeam();
    if (possessionWinner == offensiveTeam)
    {
        OffensiveResults();
    }
    else
    {
        DefensiveResults();
    }
}

void GamePlay::OffensiveResults()
{
    int offensiveResult = GameFunctions::RollOneDice(20);
    cout << endl;
    GameFunctions::DisplayRollResults(offensiveResult);
    cout << endl;
    if (offensiveResult == 1)
    {
        GameFunctions::DisplayMessage("...But an offensive flagrent foul is called! 2 free throws and the ball to the defense...");
        Team::SwitchPossession(Player1Team, Player2Team);
        ShootFreeThrows(2, true);
    }
    if (offensiveResult >= 2 && offensiveResult <= 8)
    {
        GameFunctions::DisplayMessage("...But the defense gets the stop! There is a battle for the rebound! ");
        Rebound();
    }
    if (offensiveResult >= 9 && offensiveResult <= 13)
    {
        GameFunctions::DisplayMessage("The J is money!! Two points!");
        offensiveTeam->AddToScore(2);
        DisplayScore();
        Team::SwitchPossession(Player1Team, Player2Team);
    }
    if (offensiveResult >= 14 && offensiveResult <= 15)
    {
        GameFunctions::DisplayMessage("They get the bucket and the foul! Two points with a chance for three at the free throw line!");
        offensiveTeam->AddToScore(2);
        ShootFreeThrows(1, false);
    }
    if (offensiveResult >= 16 && offensiveResult <= 19)
    {
        GameFunctions::DisplayMessage("It's cash from way downtown! Three points!");
        offensiveTeam->AddToScore(3);
        DisplayScore();
        Team::SwitchPossession(Player1Team, Player2Team);
    }
    if (offensiveResult == 20)
    {
        GameFunctions::DisplayMessage("AN INCREDIBLE SHOT FROM DISTANCE, AND A FOUL! THREE POINTS WITH A CHANCE FOR A FOUR POINT PLAY!!");
        offensiveTeam->AddToScore(3);
        ShootFreeThrows(1, false);
    }
}

void GamePlay::DefensiveResults()
{
    int defensiveResult = GameFunctions::RollOneDice(20);
    cout << endl;
    GameFunctions::DisplayRollResults(defensiveResult);
    cout << endl;
    if (defensiveResult == 1)
    {
        GameFunctions::DisplayMessage("...But the defense tries to send a message and gets called for the flagrent foul! 2 free throws and the ball back to the offense...");
        ShootFreeThrows(2, true);
    }
    if (defensiveResult >= 2 && defensiveResult <= 10)
    {
        GameFunctions::DisplayMessage("The defense gets a stop! There is a battle for the rebound!");
        Rebound();
    }
    if (defensiveResult >= 11 && defensiveResult <= 14)
    {
        GameFunctions::DisplayMessage("The defense gets a stop and they collect the rebound!");
        Team::SwitchPossession(Player1Team, Player2Team);
    }
    if (defensiveResult >= 15 && defensiveResult <= 19)
    {
        GameFunctions::DisplayMessage("The defense gets a steal! They are pushing the tempo on the fast break the other way!");
        Team::SwitchPossession(Player1Team, Player2Team);
        FastBreak();
    }
    if (defensiveResult == 20)
    {
        GameFunctions::DisplayMessage("The defense gets a breakaway steal! They finish at the rim and draw a foul! Two points with a chance for three at the free throw line!");
        Team::SwitchPossession(Player1Team, Player2Team);
        SetODTeam();
        offensiveTeam->AddToScore(2);
        ShootFreeThrows(1, false);
    }
}

void GamePlay::ShootFreeThrows(int numberOfFreeThrows, bool flagrant)
{
    SetODTeam();

    if (flagrant == false)
    {
        for (int i = 0; i < numberOfFreeThrows; i++)
        {
            int freeThrowResult = GameFunctions::RollOneDice(20);
            GameFunctions::DisplayRollResults(freeThrowResult);
            bool isLastFreeThrow = (i == (numberOfFreeThrows - 1));
            if (freeThrowResult == 1)
            {
                if (isLastFreeThrow)
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("That's a missed free throw... possession belongs to the defense and they are out on the fast break!");
                    Team::SwitchPossession(Player1Team, Player2Team);
                    FastBreak();
                }
                else
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("That's a missed free throw...");
                }
            }
            else if (freeThrowResult >= 2 && freeThrowResult <= 5)
            {
                if (isLastFreeThrow)
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("That's a missed free throw... the defense takes possession!");
                    Team::SwitchPossession(Player1Team, Player2Team);
                }
                else
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("That's a missed free throw...");
                }
            }
            else if (freeThrowResult >= 6 && freeThrowResult <= 7)
            {
                if (isLastFreeThrow)
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("That's a missed free throw... there is a battle for the rebound!");
                    Rebound();
                }
                else
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("That's a missed free throw...");
                }
            }
            else if (freeThrowResult >= 8 && freeThrowResult <= 19)
            {
                if (isLastFreeThrow)
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("The free throw is good! Change of possession!");
                    offensiveTeam->AddToScore(1);
                    Team::SwitchPossession(Player1Team, Player2Team);
                }
                else
                {
                    cout << endl;
                    GameFunctions::DisplayMessage("The free throw is good!");
                    offensiveTeam->AddToScore(1);
                }

            }
            else if (freeThrowResult == 20)
            {
                cout << endl;
                GameFunctions::DisplayMessage("The free throw is good, and the defense commits a lane violation! Take another free throw!");
                offensiveTeam->AddToScore(1);
                ShootFreeThrows(1, false);
            }
        }

        GamePlay::DisplayScore();
    }

    if (flagrant == true)
    {
        for (int i = 0; i < numberOfFreeThrows; i++)
        {
            int freeThrowResult = GameFunctions::RollOneDice(20);
            GameFunctions::DisplayRollResults(freeThrowResult);
            if (freeThrowResult >= 1 && freeThrowResult <= 7)
            {
                cout << endl;
                GameFunctions::DisplayMessage("That's a missed free throw...");
            }
            if (freeThrowResult >= 8 && freeThrowResult <= 20)
            {
                cout << endl;
                GameFunctions::DisplayMessage("The free throw is good!");
                offensiveTeam->AddToScore(1);
            }
            GamePlay::DisplayScore();
        }
    }


}

void GamePlay::FastBreak()
{
    if (Player1Team.GetPossession() == true)
    {
        Player1Team.AddToTotalDiceValue(GameFunctions::RollOneDice(10));
    }
    if (Player2Team.GetPossession() == true)
    {
        Player2Team.AddToTotalDiceValue(GameFunctions::RollOneDice(10));
    }
}

void GamePlay::Rebound()
{
    bool isTie = true;

    while (isTie == true)
    {
        cout << endl;
        cout << "     " << Player1Team.GetTeamName() << " Rebounding:" << endl;
        int player1ReboundingResult = GameFunctions::RollMultipleDice(20, Player1Team.GetStat(ES_ReboundingSkill), "High", false);
        cout << endl;
        cout << "     " << Player2Team.GetTeamName() << " Rebounding:" << endl;
        int player2ReboundingResult = GameFunctions::RollMultipleDice(20, Player2Team.GetStat(ES_ReboundingSkill), "High", false);
        cout << endl;

        if (player1ReboundingResult > player2ReboundingResult)
        {
            cout << "     " << Player1Team.GetTeamName() << " grab the rebound!" << endl;
            Player1Team.SetPossession(true);
            Player2Team.SetPossession(false);
            isTie = false;
        }
        else if (player2ReboundingResult > player1ReboundingResult)
        {
            cout << "     " << Player2Team.GetTeamName() << " grab the rebound!" << endl;
            Player2Team.SetPossession(true);
            Player1Team.SetPossession(false);
            isTie = false;
        }
        else if (player1ReboundingResult == player2ReboundingResult)
        {
            isTie = true;
        }
    }
}