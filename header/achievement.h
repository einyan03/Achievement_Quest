#ifndef _ACHIEVEMENT_H                 // Prevent multiple definitions if this 
#define _ACHIEVEMENT_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"

using namespace std;

class Achievement
{
protected:
	// Achievement properties
	bool achievementUnlock; // check to see if achievement is unlocked

public:
	// Constructor
	Achievement();

	// Destructor
	virtual ~Achievement();

	// get achivements based on current player stats
	virtual string getAchievement(int* numberOfDeaths, int* numberOfJumps, int* totalMonsterKills);

	// flags the achievement as unlocked
	void flagAchievement();

	// unflag the achievement
	void resetFlag();

	// get the achievment score
	int getFlag();
};

#endif
