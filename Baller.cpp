#include <iostream>
#include "Team.h"
#include "GameSetupMenu.h"
#include "GameFunctions.h"
#include "GamePlay.h"

using namespace std;
#include <time.h>

int main()
{
    srand((unsigned)time(0));
    GameSetupMenu SetupMenu;
    SetupMenu.RunSetup();
}