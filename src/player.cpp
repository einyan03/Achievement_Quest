#include "player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
	spriteData.width = playerNS::WIDTH;				// size of player 
	spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;						// location on screen
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;		// rectangle to select parts of an image
	spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;									// velocity X
	velocity.y = 0;									// velocity Y
	frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	startFrame = playerNS::PLAYER_START_FRAME;		// first frame of player animation
	endFrame = playerNS::PLAYER_END_FRAME;			// last frame of player animation
	currentFrame = startFrame;
	mass = playerNS::MASS;							// mass
	collisionType = entityNS::BOX;					// collision type 'bounding box'
	spriteData.scale = 0.5;
	isActive = true;
	isJumping = false;
	playerMoveX = 0;

	//-- collision detection --//
	// 4 edges of rectangle
	edge.top = -spriteData.height / 2;
	edge.bottom = spriteData.height / 2;
	edge.left = -spriteData.width / 2;
	edge.right = spriteData.width / 2;
}

//=============================================================================
// Initialize the player.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void Player::draw()
{
	Image::draw();              // draw player
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;						// move player along X 
	spriteData.y += frameTime * velocity.y;						// move player along Y	
	velocity.y += GRAVITY * frameTime;							// fall down velocity
	velocity.x = 0;
	
	// Jump movement 
	if ((input->wasKeyPressed('W') || input->wasKeyPressed(VK_UP)) && isJumping == false)
	{
		doubleJump++;
		jumpCount++;
		velocity.y = -playerNS::JUMPVELOCITY;					// set deacceleration	

		if (doubleJump > 1)
		{
			doubleJump = 0;
			stopJump();
		}
	}

	// Move left movement
	else if (input->isKeyDown('A') || input->isKeyDown(VK_LEFT))
	{
		spriteData.x += cos(getRadians() - 180 * PI / 180);
		spriteData.flipHorizontal = true;
		playerMoveX = spriteData.x;
	}	 
	// Move right movement
	else if (input->isKeyDown('D') || input->isKeyDown(VK_RIGHT))
	{
		spriteData.x += cos(getRadians() - 0 * PI / 180);
		spriteData.flipHorizontal = false;
		playerMoveX = spriteData.x;
	}

	// Boundary
	if (spriteData.x < 0)
		spriteData.x = 0;
	if (spriteData.y < 0) 		// if hit top screen edge
		spriteData.y = 0;		// position at top screen edge
}

// getter/ setter for x and y coordinates of sprite (player)
void Player::setPlayerMoveX(float x){ playerMoveX = x; }
float Player::getPlayerMoveX(){ return playerMoveX; }

void Player::allowJump() // allow player to jump
{
	isJumping = false;
}

void Player::stopJump() // prevent player from jumping
{
	isJumping = true;
}

int Player::getJumpCount()
{
	return jumpCount;
}

void Player::resetJumps()
{
	jumpCount = 0;
}

void Player::resetDoubleJump()
{
	doubleJump = 0;
}