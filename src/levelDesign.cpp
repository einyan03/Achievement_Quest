#include "levelDesign.h"

//=============================================================================
// default constructor
//=============================================================================
LevelDesign::LevelDesign() : Entity()
{
	spriteData.width = levelDesignNS::WIDTH;				// size of tiles 
	spriteData.height = levelDesignNS::HEIGHT;
	spriteData.x = levelDesignNS::X;						// location on screen
	spriteData.y = levelDesignNS::Y;
	spriteData.rect.bottom = levelDesignNS::HEIGHT;			// rectangle to select parts of an image
	spriteData.rect.right = levelDesignNS::WIDTH;
	collisionType = entityNS::BOX;							// collision type 'bounding box'
	isActive = true;

	//-- collision detection --//
	// 4 edges of rectangle
	edge.top = -spriteData.height / 2;
	edge.bottom = spriteData.height / 2;
	edge.left = -spriteData.width / 5;
	edge.right = spriteData.width / 5;
}

//=============================================================================
// Initialize the tile.
// Post: returns true if successful, false if failed
//=============================================================================
bool LevelDesign::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the enemy
//=============================================================================
void LevelDesign::draw()
{
	Image::draw();              // draw enemy
}

//=============================================================================
// Destructor
//=============================================================================
LevelDesign::~LevelDesign(){}


