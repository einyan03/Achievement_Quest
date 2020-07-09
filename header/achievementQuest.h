#ifndef _ACHIEVEMENTQUEST_H             // Prevent multiple definitions if this 
#define _ACHIEVEMENTQUEST_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "player.h"
#include "levelDesign.h"
#include "ai.h"
#include "enemy.h"

#include "achievement.h"
#include "deathAchievement.h"
#include "jumpAchievement.h"
#include "monsterAchievement.h"

//=============================================================================
// This class is the core of the game
//=============================================================================

class AchievementQuest : public Game
{
private:
	// game items
	TextureManager enemyTexture;	// eneemy texture
	TextureManager playerTexture;	// player texture
	TextureManager tileTexture;		// tiles texture
	TextureManager uiTexture;		// UI texture
	TextureManager menuTexture;		// Menu texture
	TextureManager buttonsTexture;	// button texture
	TextureManager buttonsSmallTexture; // small buttons
	TextureManager pausedUITexture;	// paused ui texture
	TextureManager exitUITexture;	// exit ui texture
	TextureManager backgroundTexture;	// background ui texture
	TextureManager miniTileTexture; // Minimap texture
	TextureManager miniPlayerTexture; //Minimap Player texture
	TextureManager winUITexture;
	TextureManager achievementRequiredTexture;

	Enemy enemy;					// enemy image
	Player  player;					// player image
	LevelDesign tile;				// tile - level design image
	LevelDesign tileTop;
	LevelDesign miniTile;		    // minimap tile
	LevelDesign playerTile;			// Minimap Player Tile
	AI enemyTileMap;				// enemy tile 

	Image menu;						// menu image
	Image ui;						// ui image
	Image pauseUI;					// paused ui image
	Image exitUI;					// exit ui image
	Image background;				// background
	Image winUI;

	Image resumeButton;				// resume button
	Image replayButton;
	Image mainMenuButton;			// main menu button
	Image exitButton;				// exit button
	Image exitYes;					// exit Yes
	Image exitNo;					// exit No
	Image achievementRequiredUI;
	Image confirmButton;

	float mapX;						// map image
	float enemyMap;

	TextDX	dxAchievementFont;		// font for achievements

	int playerJumps;				// No. of times the player jumps
	int playerDeath;				// No.of times the player dies
	int monsterKills;				// Monster kills

	bool exitConfirmation;			// exit
	bool menuOn;					// show menu
	bool showMap;					//show miniMap
	bool playerEnd;

	bool win;

	int TotalAchievements;			// Total no of achievements
	int achievementPlaceholder;		// count achievements

	Achievement* achievementList[15];

public:
	// Constructor
	AchievementQuest();

	// Destructor
	virtual ~AchievementQuest();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
	void restartGame();
};

#endif
