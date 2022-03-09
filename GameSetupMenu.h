#pragma once
using namespace std;

#include "GamePlay.h"

class GameSetupMenu
{
public:

	enum EMainMenuOption
	{
		EMM_None = 0,
		EMM_Play,
		EMM_Tutorial,
		EMM_Quit,
	};

	enum EGameTypeOption
	{
		EGT_None = 0,
		EGT_HeadToHead,
	};

	enum ETwoPlayerOption
	{
		ETP_None = 0,
		ETP_PickTeams,
		ETP_RPG,
		ETP_RandomChaos,
	};

	enum EStats
	{
		ES_OffensiveSkill = 0,
		ES_DefensiveSkill,
		ES_ReboundingSkill,
		ES_TeamStrength,
		ES_TeamConsistency,
		ES_StatCount,
	};

	// Member Functions
	void RunSetup();

	int Tutorial();
	void QuitGame();

	int DisplayMainMenu();
	void MainMenuOptions();

	int DisplayGameTypes();
	void GameTypeOptions();

	int DisplayGames();
	void GameOptions();

	void SetCoachName(Team& team);
	void SetTeamName(Team& team);
	void SetTeamStats(Team& team, int gameType);

	void SetNamingInfo(Team& team1, Team& team2);
	void SetPickedTeams(Team& team1, Team& team2);
	void SetRPGTeams(Team& team1, Team& team2);
	void SetRandomChaosTeams(Team& team1, Team& team2);

private:
	// Member Variables
	bool m_stillPlaying = true;
	int remainingBP = 7;
	GamePlay BBallGame;
};
