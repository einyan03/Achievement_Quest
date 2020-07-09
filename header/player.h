#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "entity.h"

namespace playerNS
{
	const int WIDTH = 50;								// image width
	const int HEIGHT = 93;								// image height

	const int X = 0;									// location on screen
	const int Y = 0;

	const float INITIAL_SPEED = 0;
	const float MOVEMENT_SPEED = 100;					// 100 pixels per second
	const float MASS = 300.0f;							// mass
	
	const int   TEXTURE_COLS = 3;						// texture has 3 columns
	const int   PLAYER_START_FRAME = 0;					// player starts at frame 0
	const int   PLAYER_END_FRAME = 2;					// player animation frames 0, 1, 2

	const float PLAYER_ANIMATION_DELAY = 0.2f;			// time between frames
	const float JUMPVELOCITY = 500.0f;					// velocity when player jumps
	const float XVELOCITY = 200.0f;
}

// inherits from Entity class
class Player : public Entity
{
private:
	bool isActive;
	float playerMoveX;

	bool isJumping; // check to see if player is jumping

	int jumpCount;

	int doubleJump;
public:
	// constructor
	Player();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void setPlayerMoveX(float x);
	float getPlayerMoveX();

	void allowJump();
	void stopJump();

	int getJumpCount();
	void resetJumps();
	void resetDoubleJump();
};
#endif