#include "enemy.h"

//=============================================================================
// default constructor
//=============================================================================
Enemy::Enemy() : Entity()
{
	spriteData.width = enemyNS::WIDTH;				// size of player 
	spriteData.height = enemyNS::HEIGHT;
	spriteData.x = enemyNS::X;						// location on screen
	spriteData.y = enemyNS::Y;
	spriteData.rect.bottom = enemyNS::HEIGHT;		// rectangle to select parts of an image
	spriteData.rect.right = enemyNS::WIDTH;
	velocity.x = 0;									// velocity X
	velocity.y = 0;									// velocity Y
	frameDelay = enemyNS::ENEMY_ANIMATION_DELAY;
	startFrame = enemyNS::ENEMY_START_FRAME;		// first frame of player animation
	endFrame = enemyNS::ENEMY_END_FRAME;			// last frame of player animation
	currentFrame = startFrame;
	mass = enemyNS::MASS;							// mass
	collisionType = entityNS::BOX;					// collision type 'bounding box'
	isActive = true; 

	//-- collision detection --//
	// 4 edges of rectangle
	edge.top = -spriteData.height / 2;
	edge.bottom = spriteData.height / 2;
	edge.left = -spriteData.width / 2;
	edge.right = spriteData.width / 2;

	/*ai*/
	tileX = floor(x / levelDesignNS::WIDTH);
	tileY = floor(y / levelDesignNS::HEIGHT);
	enemy_state = enemyNS::WANDER;
	timer = 0;
	playerXPos = 0;
	playerYPos = 0;
}

//=============================================================================
// Initialize the enemy.
// Post: returns true if successful, false if failed
//=============================================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the enemy
//=============================================================================
void Enemy::draw()
{
	Image::draw();              // draw enemy
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	tileX = floor(x + enemyNS::WIDTH);
	tileY = floor(y + enemyNS::HEIGHT);

	velocity.y += gravity * frameTime;	// to pull down the enemy by the gravity
}

void Enemy::ai(float frameTime)
{
	if (enemy_state == enemyNS::WANDER) 
	{
		if (getTileBelow() == 6 || getTileBelow() == 7)
		{
			velocity.x = 0;
			timer += 1;
		}

		if (timer == 100)
		{
			enemy_state = enemyNS::WAIT;
			timer = 0;
		}
	}

	if (enemy_state == enemyNS::WAIT) 
	{
		if (getTileBelow() == 6)
		{
			velocity.x = 100;
		}
		if (getTileBelow() == 7)
		{
			velocity.x = -100;
		}
		if (getTileBelow() == 0)
		{
			enemy_state = enemyNS::WANDER;
		}
	}
}

int Enemy::getTileBelow()
{
	return a.getTile(tileY + 1, tileX);
}

int Enemy::getTileAhead()
{
	if (velocity.x < 0)
	{
		return a.getTile(tileY, tileX - 1);
	}
	if (velocity.x > 0)
	{
		return a.getTile(tileY, tileX + 1);
	}
	if (velocity.x == 0)
	{
		return -1;
	}
}

void Enemy::setPlayerPos(float pX, float pY)
{
	playerXPos = pX;
	playerYPos = pY;
}

float Enemy::getPlayerDist()
{
	return sqrt((x - playerXPos) * (x - playerXPos) + (y - playerYPos) * (y - playerYPos));
}

float Enemy::getPlayerAngle()
{
	return atan2(x - playerXPos, y - playerYPos);
}

float Enemy::getTileX()
{
	return x;
}

float Enemy::getTileY()
{
	return y;
}
