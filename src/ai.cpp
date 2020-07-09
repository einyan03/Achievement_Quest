#include "ai.h"

//=============================================================================
// default constructor
//=============================================================================
AI::AI()
{}

//=============================================================================
// Initialize the tile.
// Post: returns true if successful, false if failed
//=============================================================================
bool AI::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void AI::copyLevelDesignMap()
{
	for (int i = 0; i < levelDesignNS::MAP_HEIGHT; i++)
	{
		for (int j = 0; j < levelDesignNS::MAP_WIDTH; j++)
		{
			if (levelDesignNS::tileMap[i][j] >= 0 && levelDesignNS::tileMap[i][j] <= 4) 
			{
				newTileMap[i][j] = levelDesignNS::tileMap[i][j];
			}
			else
			{
				newTileMap[i][j] = -1;			// empty
			}
		}
	}
}

void AI::loadTileMapWithEnemy()
{
	for (int row = 0; row < levelDesignNS::MAP_HEIGHT; row++)
	{
		for (int col = 0; col < levelDesignNS::MAP_WIDTH; col++)
		{
			// current block is tile and there is no block above
			if (newTileMap[row][col] == 0 && newTileMap[row - 1][col] == -1)		
			{
				// check if it is only one tile
				if (newTileMap[row][col - 1] == -1 && newTileMap[row][col + 1] == -1)
				{
					newTileMap[row][col] = 5;  
				}

				// check the left side of the platform (platform outrange on the left side)
				if ((newTileMap[row][col - 1] == -1 || newTileMap[row][col - 1] == 1 || newTileMap[row][col - 1] == 2)
					&& newTileMap[row][col + 1] == 0)
				{
					newTileMap[row][col] = 6;			//set the left tile
				}

				// check the right side of the platform (platform outrange on the right side)
				if (newTileMap[row][col - 1] == 1 &&
					(newTileMap[row][col + 1] == -1 || newTileMap[row][col + 1] == 1 || newTileMap[row][col + 1] == 4))
				{
					newTileMap[row][col] = 7;			//set the right tile
				}
			}
		}
	}
}

int AI::getTile(int x, int y)
{
	return newTileMap[x][y];
}

AI::~AI()
{}
