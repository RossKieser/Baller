#include <iostream>
#include "Team.h"
#include "GameSetupMenu.h"
#include "GameFunctions.h"
#include "GamePlay.h"

using namespace std;

// Constructors
Team::Team()
{
	m_coachName = "Coach";
	m_teamName = "Team";
	for (int i = 0; i < 5; i++)
	{
		m_stats[i] = 1;
	}

	m_score = 0;
	m_targetScore = 10;

	m_hasPossession = false;
	m_totalDiceValue = 0;
}

Team::Team(std::string coach, std::string team, int stats[], int score, int targetScore)
{
	m_coachName = coach;
	m_teamName = team;
	m_stats[ES_OffensiveSkill] = stats[ES_OffensiveSkill];
	m_stats[ES_DefensiveSkill] = stats[ES_DefensiveSkill];
	m_stats[ES_ReboundingSkill] = stats[ES_ReboundingSkill];
	m_stats[ES_TeamStrength] = stats[ES_TeamStrength];
	m_stats[ES_TeamConsistency] = stats[ES_TeamConsistency];

	m_score = 0;
	m_targetScore = 10;

	m_hasPossession = false;
	m_totalDiceValue = 0;
}

// Destructors 
Team::~Team()
{

}

// Member Functions
void Team::DisplayTeamInfo()
{
	cout << "     " << "Your coach name is: " << m_coachName << endl;
	cout << "     " << "Your team name is: " << m_teamName << endl;
	cout << "     " << "Your Offensive Skill is: " << m_stats[ES_OffensiveSkill] << endl;
	cout << "     " << "Your Defensive Skill is: " << m_stats[ES_DefensiveSkill] << endl;
	cout << "     " << "Your Rebounding Skill is: " << m_stats[ES_ReboundingSkill] << endl;
	cout << "     " << "Your Team Strength is: " << m_stats[ES_TeamStrength] << endl;
	cout << "     " << "Your Team Consistency is: " << m_stats[ES_TeamConsistency] << endl;
}

void Team::DisplayBothTeamInfo(Team& team1, Team& team2)
{
	GameFunctions::ClearScreen();
	team1.DisplayTeamInfo();
	cout << endl;
	team2.DisplayTeamInfo();
	cout << endl;
}


void Team::SetCoachName(std::string coachName)
{
	m_coachName = coachName;
}

string Team::GetCoachName()
{
	return m_coachName;
}


void Team::SetTeamName(std::string teamName)
{
	m_teamName = teamName;
}

string Team::GetTeamName()
{
	return m_teamName;
}


void Team::SetStat(int index, int value)
{
	if (index >= ES_OffensiveSkill && index <= ES_TeamConsistency)
	{
		m_stats[index] = value;
	}
	else
	{
		cout << "     " << "Error!" << endl;
	}
}

int Team::GetStat(int index)
{

	if (index >= ES_OffensiveSkill && index <= ES_TeamConsistency)
	{
		return m_stats[index];
	}
	else
	{
		cout << "     " << "Error!" << endl;
		return 0;
	}
}

Team* Team::CompareHighestStat(Team& team1, Team& team2, int index)
{
	if (team1.GetStat(index) > team2.GetStat(index))
	{
		return &team1;
	}
	else if (team1.GetStat(index) < team2.GetStat(index))
	{
		return &team2;
	}
	else
	{
		return nullptr;
	}
}


void Team::SetPossession(bool hasPossession)
{
	m_hasPossession = hasPossession;
}

bool Team::GetPossession()
{
	return m_hasPossession;
}

void Team::SwitchPossession(Team& team1, Team& team2)
{
	if (team1.GetPossession() == true)
	{
		team1.SetPossession(false);
		team2.SetPossession(true);
	}
	else if (team1.GetPossession() == false)
	{
		team1.SetPossession(true);
		team2.SetPossession(false);
	}
}


void Team::AddToScore(int points)
{
	m_score += points;
}

void Team::SetScore(int points)
{
	m_score = points;
}

int Team::GetScore()
{
	return m_score;
}


void Team::AddToTargetScore(int spread)
{
	m_targetScore += spread;
}

void Team::SetTargetScore(int score)
{
	m_targetScore = score;
}

int Team::GetTargetScore()
{
	return m_targetScore;
}


void Team::AddToTotalDiceValue(int diceValue)
{
	m_totalDiceValue += diceValue;
}

void Team::SetTotalDiceValue(int diceValue)
{
	m_totalDiceValue = diceValue;
}

int Team::GetTotalDiceValue()
{
	return m_totalDiceValue;
}

void Team::ResetDiceTotal(Team& team1, Team& team2, int diceValue)
{
	team1.SetTotalDiceValue(diceValue);
	team2.SetTotalDiceValue(diceValue);
}
