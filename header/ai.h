#ifndef _AI_H                 // Prevent multiple definitions if this 
#define _AI_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "levelDesign.h"

class AI : public Entity
{
private:
	int newTileMap[levelDesignNS::MAP_HEIGHT][levelDesignNS::MAP_WIDTH];
public:
	AI();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	
	void copyLevelDesignMap();
	void loadTileMapWithEnemy();
	int getTile(int, int);
	~AI();
};
#endif