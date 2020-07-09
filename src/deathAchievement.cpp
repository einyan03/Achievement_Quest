#include "deathAchievement.h"

//=============================================================================
// Constructor
//=============================================================================
DeathAchievement::DeathAchievement()
{

}

DeathAchievement::DeathAchievement(int deaths)
{
	numberOfDeaths = deaths;
}

DeathAchievement::~DeathAchievement()
{
	numberOfDeaths = NULL;
}

string DeathAchievement::getAchievement(int* playerDeathCount, int* playerJumpCount, int* playerMonsterKills)
{
	if ((*playerDeathCount >= numberOfDeaths) || achievementUnlock == true)
	{
		if (achievementUnlock == false)
		{
			flagAchievement(); // unlock achievement
		}

		return "Died " + to_string(numberOfDeaths) + " times";
	}

	else
		return "---Locked---";
}
