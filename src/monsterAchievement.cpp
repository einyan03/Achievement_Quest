#include "monsterAchievement.h"

//=============================================================================
// Constructor
//=============================================================================
MonsterAchievement::MonsterAchievement()
{

}

MonsterAchievement::MonsterAchievement(int monstersToKill)
{
	killed = monstersToKill;
}

MonsterAchievement::~MonsterAchievement()
{
	killed = NULL;
}

string MonsterAchievement::getAchievement(int* playerDeathCount, int* playerJumpCount, int* playerMonsterKills)
{
	if ((*playerMonsterKills >= killed) || achievementUnlock == true)
	{

		if (achievementUnlock == false)
		{
			flagAchievement(); // unlock achievement
		}
		return to_string(killed) + " Monster kill";
	}
	else
		return "---Locked---";
}