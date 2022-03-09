#pragma once
#include<string>

using namespace std;


class Team
{
public:
	int g_GameType;
	enum EStats
	{
		ES_OffensiveSkill = 0,
		ES_DefensiveSkill,
		ES_ReboundingSkill,
		ES_TeamStrength,
		ES_TeamConsistency,
		ES_StatCount,
	};

	// Constructors
	Team();
	Team(string coach, string team, int stats[], int score, int targetScore);

	// Destructors 
	~Team();

	// Member Functions

	void DisplayTeamInfo();
	static void DisplayBothTeamInfo(Team& team1, Team& team2);

	void SetCoachName(string coachName);
	string GetCoachName();

	void SetTeamName(string teamName);
	string GetTeamName();


	void SetStat(int index, int value);
	int GetStat(int index);
	static Team* CompareHighestStat(Team& team1, Team& team2, int index);

	void SetPossession(bool hasPossession);
	bool GetPossession();
	static void SwitchPossession(Team& team1, Team& team2);

	void AddToScore(int points);
	void SetScore(int points);
	int GetScore();

	void AddToTargetScore(int spread);
	void SetTargetScore(int score);
	int GetTargetScore();

	void AddToTotalDiceValue(int diceValue);
	void SetTotalDiceValue(int diceValue);
	int GetTotalDiceValue();
	static void ResetDiceTotal(Team& team1, Team& team2, int diceValue);


private:
	// Member Variables
	string m_coachName;
	string m_teamName;

	int m_stats[ES_StatCount];
	bool m_hasPossession;
	int m_score;
	int m_targetScore;
	int m_totalDiceValue;
};
