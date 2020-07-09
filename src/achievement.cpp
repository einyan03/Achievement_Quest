#include "achievement.h"

//=============================================================================
// Constructor
//=============================================================================
Achievement::Achievement()
{
	achievementUnlock = false;
}

Achievement::~Achievement()
{

}

string Achievement::getAchievement(int* numberOfDeaths, int* numberOfJumps, int* totalMonsterKills)
{
	return "0";
}

void Achievement::flagAchievement()
{
	achievementUnlock = true;
}

int Achievement::getFlag()
{
	if (achievementUnlock == false)
		return 0;
	else
		return 1;
}

void Achievement::resetFlag()
{
	achievementUnlock = false;
}