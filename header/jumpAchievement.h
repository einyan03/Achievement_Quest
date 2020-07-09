#ifndef _JUMPACHIEVEMENT_H               // Prevent multiple definitions if this 
#define _JUMPACHIEVEMENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "achievement.h"
#include "game.h"

class JumpAchievement : public Achievement
{
	//properties
protected:
	int numberOfJumps;

public:
	// Constructor
	JumpAchievement();

	JumpAchievement(int jumps);
	// Destructor
	virtual ~JumpAchievement();

	string getAchievement(int* playerDeathCount, int* playerJumpCount, int* playerMonsterKills);
};

#endif
