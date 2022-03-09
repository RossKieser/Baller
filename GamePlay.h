#pragma once
#include "Team.h"
using namespace std;


class GamePlay
{
public:

	enum EStats
	{
		ES_OffensiveSkill = 0,
		ES_DefensiveSkill,
		ES_ReboundingSkill,
		ES_TeamStrength,
		ES_TeamConsistency,
		ES_StatCount,
	};

	enum ETwoPlayerOption
	{
		ETP_None = 0,
		ETP_PickTeams,
		ETP_RPG,
		ETP_RandomChaos,
	};

	enum EODChoices
	{
		EOD_None = 0,
		EOD_Add,
		EOD_Subtract,
		EOD_AddToOpponent,
	};

	// Member Functions

	void PlayBasketball();

	void DetermineBothTargetScores(Team& team1, Team& team2);
	void DetermineIndividualTargetScores(Team& team);
	void Tipoff();
	void PlayBall();
	void GameOver();

	void SetODTeam();
	void SetActiveTeam();
	void SwitchActiveTeam();
	string GetTeamNameFromPointer(Team* pointerName);
	void DisplayODTeam();

	void DisplayScore();

	void DesignateODRolls();
	Team* CompareODRolls();
	void ResolvePossession(Team* possessionWinner);
	void OffensiveResults();
	void DefensiveResults();
	void ShootFreeThrows(int numberOfFreeThrows, bool flagrent);
	void FastBreak();
	void Rebound();

	Team& GetPlayer1Team() { return Player1Team; }
	Team& GetPlayer2Team() { return Player2Team; }

protected:
	Team Player1Team;
	Team Player2Team;

	Team* activeTeam = nullptr;
	Team* inactiveTeam = nullptr;
	Team* offensiveTeam = nullptr;
	Team* defensiveTeam = nullptr;
};
