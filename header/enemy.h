#ifndef _ENEMY_H                 // Prevent multiple definitions if this 
#define _ENEMY_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "entity.h"
#include "ai.h"

namespace enemyNS
{
	enum ENEMY_STATE { WANDER, WAIT };
	const int WIDTH = 32;								// image width
	const int HEIGHT = 32;								// image height

	const int X = 0;									// location on screen
	const int Y = 0;

	const float INITIAL_SPEED = 0;
	const float MOVEMENT_SPEED = 100;					// 100 pixels per second
	const float MASS = 300.0f;							// mass

	const int   TEXTURE_COLS = 2;						// texture has 2 columns
	const int   ENEMY_START_FRAME = 0;					// enemy starts at frame 0
	const int   ENEMY_END_FRAME = 1;					// enemy animation frames 0, 1

	const float ENEMY_ANIMATION_DELAY = 0.2f;			// time between frames
	// const float JUMPVELOCITY = 500.0f;					// velocity when enemy jumps
}

// inherits from Entity class
class Enemy : public Entity
{
private:
	enemyNS::ENEMY_STATE enemy_state;
	bool isActive;
	float x;
	float y;
	int tileX;
	int tileY;
	AI a;
	int state;
	float timer;
	float playerXPos;
	float playerYPos;
public:
	// constructor
	Enemy();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, 
		TextureManager *textureM);
	void update(float frameTime);

	void ai(float frameTime);
	void collision(float pXvelocity, float pYvelocity);
	int getTileBelow();
	int getTileAhead();
	float getTileX();
	float getTileY();
	void setPlayerPos(float, float);
	float getPlayerDist();
	float getPlayerAngle();
};
#endif