#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }


//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Achievement Quest";
const char GAME_TITLE[] = "Achievement Quest";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1024;               // width of game in pixels
const UINT GAME_HEIGHT = 704;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;						// the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;						// the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;			// minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;		// maximum time used in calculations
const float GRAVITY = 1000.0f;							// gravitational constant
const UINT  TILE_MAP_WIDTH = 92;						// width of tile map in tiles
const UINT  TILE_MAP_HEIGHT = 21;						// height of tile map in tiles

// graphic images
const char PLAYER_IMAGE[] = "pictures\\player.png";					// player
const char TILE_IMAGE[] = "pictures\\tile.png";						// tiles
const char ENEMY_IMAGE[] = "pictures\\enemy.png";					// enemy
const char MENU_IMAGE[] = "pictures\\Menu.png";						// menu
const char UI_IMAGE[] = "pictures\\UI.png";							// ui
const char BUTTONS_IMAGE[] = "pictures\\Buttons.png";				// buttons
const char SMALL_BUTTONS_UI_IMAGE[] = "pictures\\smallButtons.png";	// pause ui
const char PAUSE_UI_IMAGE[] = "pictures\\Pause.png";				// pause ui
const char WIN_UI_IMAGE[] = "pictures\\Win.png";
const char EXIT_UI_IMAGE[] = "pictures\\exitGame.png";				// pause ui
const char BACKGROUND_IMAGE[] = "pictures\\background.png";			// pause ui
const char MINI_TILE_IMAGE[] = "pictures\\tileMini.png";			//minimap
const char MINI_PLAYER_IMAGE[] = "pictures\\playerMini.png";		//minimap
const char ACHIEVEMENT_IMAGE[] = "pictures\\RequiredAchievements.png";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY = VK_MENU;         // Alt key
const UCHAR ENTER_KEY = VK_RETURN;     // Enter key

// controls 
const UCHAR PLAYER_UP_KEY = 0x57;		// W
const UCHAR PLAYER_LEFT_KEY = 0x41;		// A
const UCHAR PLAYER_RIGHT_KEY = 0x44;	// D
const UCHAR PLAYER_DOWN_KEY = 0x53;		// S

#endif
