#include "jumpAchievement.h"

//=============================================================================
// Constructor
//=============================================================================
JumpAchievement::JumpAchievement()
{

}

JumpAchievement::JumpAchievement(int jumps)
{
	numberOfJumps = jumps;
}

JumpAchievement::~JumpAchievement()
{
	numberOfJumps = NULL;
}

string JumpAchievement::getAchievement(int* playerDeathCount, int* playerJumpCount, int* playerMonsterKills)
{
	if ((*playerJumpCount >= numberOfJumps) || achievementUnlock == true)
	{
		if (achievementUnlock == false)
		{
			flagAchievement(); // unlock achievement
		}

		return "Jump " + to_string(numberOfJumps) + " times";

	}

	else
		return "---Locked---";
}
