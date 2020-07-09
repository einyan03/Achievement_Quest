#ifndef _MONSTERACHIEVEMENT_H               // Prevent multiple definitions if this 
#define _MONSTERACHIEVEMENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "achievement.h"
#include "game.h"

class MonsterAchievement : public Achievement
{
	//properties
protected:
	int killed;

public:
	// Constructor
	MonsterAchievement();

	MonsterAchievement(int monstersToKill);
	// Destructor
	virtual ~MonsterAchievement();

	string getAchievement(int* playerDeathCount, int* playerJumpCount, int* playerMonsterKills);
};

#endif
