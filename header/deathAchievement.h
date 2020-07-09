#ifndef _DEATHACHIEVEMENT_H               // Prevent multiple definitions if this 
#define _DEATHACHIEVEMENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "achievement.h"
#include "game.h"

class DeathAchievement : public Achievement
{
	//properties
protected:
	int numberOfDeaths;

public:
	// Constructor
	DeathAchievement();

	DeathAchievement(int numberOfDeaths);

	// Destructor
	virtual ~DeathAchievement();

	string getAchievement(int* playerDeathCount, int* playerJumpCount, int* playerMonsterKills);
};

#endif
