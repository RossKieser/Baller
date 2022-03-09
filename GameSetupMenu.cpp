#include <iostream>
#include "Team.h"
#include "GameSetupMenu.h"
#include "GameFunctions.h"
#include "GamePlay.h"

using namespace std;

// Member Functions
void GameSetupMenu::RunSetup()
{
    MainMenuOptions();
}


int GameSetupMenu::Tutorial()
{
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Do you have what it takes to lead your team to victory?");
    GameFunctions::DisplayMessage("In this thrilling game, you will go head to head with a friend to prove who is the real baller.");
    GameFunctions::DisplayMessage("You have 5 stats that impact your performance: Offensive Skill, Defensive Skill, Rebounding, Team Strength, and Team Consistency.");
    GameFunctions::DisplayMessage("Your stats depend on the game mode or team you pick. The maximum level for each stat is 5.");
    cout << endl;
    GameFunctions::DisplayMessage("The Offensive Skill stat impacts your consistency on offense (# of dice rolled per offensive roll).");
    GameFunctions::DisplayMessage("The Defensive Skill stat impacts your consistency on defense (# of dice rolled per defensive roll).");
    GameFunctions::DisplayMessage("The Rebounding stat impacts your consistency rebounding the ball (# of dice rolled per rebounding roll).");
    GameFunctions::DisplayMessage("The Team Strength stat impacts you potential advantage over your opponent before each game (Determines which dice is rolled when determining game spread).");
    GameFunctions::DisplayMessage("The Team Consistency stat impacts your teams ability to perform consistently from game to game (# of dice rolled per game spread roll).");
    cout << endl;
    GameFunctions::DisplayMessage("During each offensive possesion, 3 dice rolls are made. after each roll you must decide if you want to add, subract, or add to your opponets total (the difference from 15 (x2)). You must do each option once and only once.");
    GameFunctions::DisplayMessage("The defense does the same. Whichever team gets the higher total result of all 3 rolls is successful during the possession.");
    GameFunctions::DisplayMessage("If the rolls are equal value, the team with highest team strength is successful during the possession.  If the team strengths are also equal, the home team is successful during the possession.");
    GameFunctions::DisplayMessage("The higher rolling team rolls another D20 Die to determine the ultimate result of the possesion");
    GameFunctions::DisplayMessage("A high roll of the D20 results in points for the offense or a fast break opportunity for the defense, but a poor roll can still result in disaster!");
    cout << endl;
    GameFunctions::DisplayMessage("If you get a fast break opportunity, a D10 is rolled and added to your next offensive possesion roll.");
    GameFunctions::DisplayMessage("If a shot is missed or the defense gets a clean stop, a D20 rebounding roll takes place. The highest roller secures the rebound.");
    GameFunctions::DisplayMessage("If a foul is called, the shooting team rolls a D20 and a high roll results in a point, and a low roll results in a miss");
    cout << endl;
    GameFunctions::DisplayMessage("Before each game, the betting line is determined. Depending on team strength and consistency, each team rolls die and adds result + 10. That number is the target score.");
    GameFunctions::DisplayMessage("Ready to end the tutorial? Press 1 to end tutorial or any other number to end program: ", true);
    int choice = GameFunctions::GetInteger();
    return choice;
}

void GameSetupMenu::QuitGame()
{
    GameFunctions::DisplayMessage("Goodbye!");
    m_stillPlaying = false;
}


int GameSetupMenu::DisplayMainMenu()
{
    GameFunctions::DisplayMessage("Welcome to Baller. Do have what it takes to lead your team to greatness?");
    GameFunctions::DisplayMessage("Choose an option:");
    GameFunctions::DisplayMessage("1) Play");
    GameFunctions::DisplayMessage("2) Tutorial");
    GameFunctions::DisplayMessage("3) Quit ");
    int choice = GameFunctions::GetInteger();
    return choice;
}

void GameSetupMenu::MainMenuOptions()
{
    int menuOption = DisplayMainMenu();
    switch (menuOption)
    {
    case EMM_Play:
    {
        GameTypeOptions();
        break;
    }
    case EMM_Tutorial:
    {
        int tutorialChoice = Tutorial();
        if (tutorialChoice == EMM_Play)
        {
            GameFunctions::ClearScreen();
            GameTypeOptions();
        }
        else
        {
            QuitGame();
        }
        break;
    }
    case EMM_Quit:
    {
        QuitGame();
        break;
    }
    default:
    {
        GameFunctions::ClearScreen();
        GameFunctions::DisplayMessage("Invalid entry, try again!");
        break;
    }
    }
}


int GameSetupMenu::DisplayGameTypes()
{
    GameFunctions::DisplayMessage("Are you ready to play?");
    GameFunctions::DisplayMessage("Choose an option:");
    GameFunctions::DisplayMessage("1) Head to Head");
    GameFunctions::DisplayMessage("2) Quit ");
    int choice = GameFunctions::GetInteger();
    return choice;
}

void GameSetupMenu::GameTypeOptions()
{
    cout << endl;
    int gameType = DisplayGameTypes();
    switch (gameType)
    {
    case EGT_HeadToHead:
    {
        GameOptions();
        BBallGame.PlayBasketball();
        QuitGame();
        break;
    }
    default:
    {
        GameFunctions::ClearScreen();
        GameFunctions::DisplayMessage("Goodbye!");
        break;
    }
    }
}

int GameSetupMenu::DisplayGames()
{
    GameFunctions::DisplayMessage("How do you want teams to be picked?");
    GameFunctions::DisplayMessage("Choose an option:");
    GameFunctions::DisplayMessage("1) Pick Teams (all stats the same)");
    GameFunctions::DisplayMessage("2) RPG (Each player gets 7 skill points to customize their team)");
    GameFunctions::DisplayMessage("3) Random Chaos (Each player gets a team with completely random stats)");
    GameFunctions::DisplayMessage("4) Quit ");
    int choice = GameFunctions::GetInteger();
    return choice;
}

void GameSetupMenu::GameOptions()
{
    SetNamingInfo(BBallGame.GetPlayer1Team(), BBallGame.GetPlayer2Team());
    int twoPlayerGameType = DisplayGames();
    switch (twoPlayerGameType)
    {
    case ETP_PickTeams:
    {
        SetPickedTeams(BBallGame.GetPlayer1Team(), BBallGame.GetPlayer2Team());
        break;
    }
    case ETP_RPG:
    {
        SetRPGTeams(BBallGame.GetPlayer1Team(), BBallGame.GetPlayer2Team());
        break;
    }
    case ETP_RandomChaos:
    {
        SetRandomChaosTeams(BBallGame.GetPlayer1Team(), BBallGame.GetPlayer2Team());
        break;
    }
    default:
    {
        break;
    }
    }
}

void GameSetupMenu::SetCoachName(Team& team)
{
    GameFunctions::DisplayMessage("What is your coaches name? ");
    string coachName = GameFunctions::GetString();
    team.SetCoachName(coachName);
}

void GameSetupMenu::SetTeamName(Team& team)
{
    GameFunctions::DisplayMessage("What is your team name? ");
    string teamName = GameFunctions::GetString();
    team.SetTeamName(teamName);
}

void GameSetupMenu::SetTeamStats(Team& team, int gameType)
{
    if (gameType == ETP_PickTeams)
    {
        bool validOption = false;
        do
        {
            GameFunctions::DisplayMessage("1) One Star (all stats)");
            GameFunctions::DisplayMessage("2) Two Star (all stats)");
            GameFunctions::DisplayMessage("3) Three Star (all stats)");
            GameFunctions::DisplayMessage("4) Four Star (all stats)");
            GameFunctions::DisplayMessage("5) Five Star (all stats)");
            int teamChoice = GameFunctions::GetInteger();
            if (teamChoice >= 1 && teamChoice <= 5)
            {
                for (int i = 0; i < 5; i++)
                {
                    team.SetStat(i, teamChoice);
                }
                validOption = true;
            }
            else
            {
                GameFunctions::DisplayMessage("Invalid Option. Try Again!");
                validOption = false;
            }
        } while (!validOption);
    }
    else if (gameType == ETP_RPG)
    {
        remainingBP = 7;
        bool validInput = false;
        cout << endl;
        GameFunctions::DisplayMessage("You have 7 Baller Points to allocate between Offensive Skill, Defensive Skill, and Rebounding Skill. All stats are given 1 BP to start (Putting 3 BP into offensive skill would make it a 4 overall).");
        GameFunctions::DisplayMessage("The Team Strength and Consisttency stats are defaulted at 3. These can't be changed. 4 BP is the max for 1 stat (for an overall max stat of 5)");

        while (validInput == false)
        {
            cout << endl;
            cout << "     " << "You have " << remainingBP << " BP remaining!" << endl;
            GameFunctions::DisplayMessage("Enter how many BP you would like to spend on Offensive Skill: ");
            int offensiveBP = GameFunctions::GetInteger();
            if (offensiveBP >= 5)
            {
                GameFunctions::DisplayMessage("That would put the stat over the maximum of 5 (4 BP Max)! Please try again!");
                validInput = false;
            }
            else if (offensiveBP < remainingBP)
            {
                team.SetStat(ES_OffensiveSkill, (1 + offensiveBP));
                remainingBP = remainingBP - offensiveBP;
                validInput = true;
            }
            else if (offensiveBP >= remainingBP)
            {
                GameFunctions::DisplayMessage("You don't have enough BP remaining! Please try again!");
                validInput = false;
            }
        }
        validInput = false;
        while (validInput == false)
        {
            cout << endl;
            cout << "     " << "You have " << remainingBP << " BP remaining!" << endl;
            GameFunctions::DisplayMessage("Enter how many BP you would like to spend on Defensive Skill: ");
            int defensiveBP = GameFunctions::GetInteger();
            if (defensiveBP >= 5)
            {
                GameFunctions::DisplayMessage("That would put the stat over the maximum of 5 (4 BP Max)! Please try again!");
                validInput = false;
            }
            else if (defensiveBP < remainingBP)
            {
                team.SetStat(ES_DefensiveSkill, (1 + defensiveBP));
                remainingBP = remainingBP - defensiveBP;
                validInput = true;
            }
            else if (defensiveBP >= remainingBP)
            {
                GameFunctions::DisplayMessage("You don't have enough BP remaining! Please try again!");
                validInput = false;
            }
        }
        validInput = false;
        while (validInput == false)
        {
            cout << endl;
            cout << "     " << "You have " << remainingBP << " BP remaining!" << endl;
            GameFunctions::DisplayMessage("Enter how many BP you would like to spend on Rebounding Skill: ");
            int reboundingBP = GameFunctions::GetInteger();
            if (reboundingBP >= 5)
            {
                GameFunctions::DisplayMessage("That would put the stat over the maximum of 5 (4 BP Max)! Please try again!");
                validInput = false;
            }
            else if (reboundingBP <= remainingBP)
            {
                team.SetStat(ES_ReboundingSkill, (1 + reboundingBP));
                remainingBP = remainingBP - reboundingBP;
                validInput = true;
            }
            else if (reboundingBP > remainingBP)
            {
                GameFunctions::DisplayMessage("You don't have enough BP remaining! Please try again!");
                validInput = false;
            }
        }
        team.SetStat(ES_TeamConsistency, 3);
        team.SetStat(ES_TeamStrength, 3);
    }
    else if (gameType == ETP_RandomChaos)
    {
        for (int i = 0; i < 5; i++)
        {
            team.SetStat(i, GameFunctions::RollOneDice(5));
        }
        int averageStatValue = (team.GetStat(ES_OffensiveSkill) + team.GetStat(ES_DefensiveSkill)) / 2;
        team.SetStat(ES_TeamStrength, averageStatValue);
    }
}


void GameSetupMenu::SetNamingInfo(Team& team1, Team& team2)
{
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Home Team");
    SetCoachName(team1);
    SetTeamName(team1);
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Road Team");
    SetCoachName(team2);
    SetTeamName(team2);
    GameFunctions::ClearScreen();
}

void GameSetupMenu::SetPickedTeams(Team& team1, Team& team2)
{
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Player 1, Pick your team:");
    SetTeamStats(team1, ETP_PickTeams);
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Player 2, Pick your team:");
    SetTeamStats(team2, ETP_PickTeams);
}

void GameSetupMenu::SetRPGTeams(Team& team1, Team& team2)
{
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Player 1, Pick your team:");
    SetTeamStats(team1, ETP_RPG);
    GameFunctions::ClearScreen();
    GameFunctions::DisplayMessage("Player 2, Pick your team:");
    SetTeamStats(team2, ETP_RPG);
}

void GameSetupMenu::SetRandomChaosTeams(Team& team1, Team& team2)
{
    SetTeamStats(team1, ETP_RandomChaos);
    SetTeamStats(team2, ETP_RandomChaos);
}