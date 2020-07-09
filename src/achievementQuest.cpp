#include "achievementQuest.h"

//=============================================================================
// Constructor
//=============================================================================
AchievementQuest::AchievementQuest()
{
	mapX = 0;
	showMap = true;
	menuOn = true;
	playerEnd = false;
	paused = true;
	playerWin = true;
	achievementRequired = true;
	exitConfirmation = false;
	TotalAchievements = 0;

	playerJumps = player.getJumpCount();
	playerDeath = 0;
	monsterKills = 0;

	achievementList[14] = new JumpAchievement(1);
	achievementList[13] = new JumpAchievement(7);
	achievementList[12] = new JumpAchievement(15);
	achievementList[11] = new JumpAchievement(25);
	achievementList[10] = new JumpAchievement(30);
	achievementList[9] = new JumpAchievement(35);
	achievementList[8] = new JumpAchievement(45);
	achievementList[7] = new JumpAchievement(50);
	achievementList[6] = new DeathAchievement(1);
	achievementList[5] = new DeathAchievement(2);
	achievementList[4] = new DeathAchievement(3);
	achievementList[3] = new DeathAchievement(4);
	achievementList[2] = new DeathAchievement(5);
	achievementList[1] = new DeathAchievement(6);
	achievementList[0] = new DeathAchievement(7);

	// play background music
	PlaySound("sound\\Lonely.wav", NULL, SND_LOOP | SND_ASYNC);
}

//=============================================================================
// Destructor
//=============================================================================
AchievementQuest::~AchievementQuest()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void AchievementQuest::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError
	// background
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing small buttons texture"));

	// exit button
	if (!buttonsSmallTexture.initialize(graphics, SMALL_BUTTONS_UI_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing small buttons texture"));

	// exit confirmation
	if (!exitUITexture.initialize(graphics, EXIT_UI_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing exit ui texture"));

	// pause ui
	if (!pausedUITexture.initialize(graphics, PAUSE_UI_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause ui texture"));

	// 
	if (!achievementRequiredTexture.initialize(graphics, ACHIEVEMENT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing achievement ui texture"));

	// win ui 
	if (!winUITexture.initialize(graphics, WIN_UI_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing win ui texture"));

	// button textures
	if (!buttonsTexture.initialize(graphics, BUTTONS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing buttons texture"));

	// menu textures
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	// ui textures
	if (!uiTexture.initialize(graphics, UI_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ui texture"));

	// player textures
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));

	// tile textures - level design
	if (!tileTexture.initialize(graphics, TILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));

	// minimaptile textures - level design
	if (!miniTileTexture.initialize(graphics, MINI_TILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));

	// minimapplayer textures - level design
	if (!miniPlayerTexture.initialize(graphics, MINI_PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile texture"));

	// player image
	if (!player.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));

	// tile & spike image
	if (!tile.initialize(this, levelDesignNS::TEXTURE_SIZE, levelDesignNS::TEXTURE_SIZE, levelDesignNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// mini tile & spike image
	if (!miniTile.initialize(this, levelDesignNS::MINIMAP_TEXTURE_SIZE, levelDesignNS::MINIMAP_TEXTURE_SIZE, levelDesignNS::MINIMAP_TEXTURE_COLS, &miniTileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// mini player image
	if (!playerTile.initialize(this, levelDesignNS::MINIMAP_TEXTURE_SIZE, levelDesignNS::MINIMAP_TEXTURE_SIZE, levelDesignNS::MINIMAP_TEXTURE_COLS, &miniPlayerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// ui image
	if (!ui.initialize(graphics, 0, 0, 0, &uiTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ui"));

	// menu image
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	// resume Button
	if (!resumeButton.initialize(graphics, 0, 0, 0, &buttonsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing resume button"));
	resumeButton.setX(GAME_WIDTH / 2 - resumeButton.getCenterX());
	resumeButton.setY(GAME_HEIGHT / 2.5 - resumeButton.getCenterY());

	// Main menu button
	if (!mainMenuButton.initialize(graphics, 0, 0, 0, &buttonsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu button"));
	mainMenuButton.setX(GAME_WIDTH / 2 - mainMenuButton.getCenterX());
	mainMenuButton.setY(GAME_HEIGHT / 2 - mainMenuButton.getCenterY());

	// exit button
	if (!exitButton.initialize(graphics, 0, 0, 0, &buttonsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing exit button"));
	exitButton.setX(GAME_WIDTH / 2 - exitButton.getCenterX());
	exitButton.setY(GAME_HEIGHT / 1.65 - exitButton.getCenterY());

	// exit YES button
	if (!exitYes.initialize(graphics, 0, 0, 0, &buttonsSmallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing exit button"));
	exitYes.setX(GAME_WIDTH / 3 - exitYes.getCenterX());
	exitYes.setY(GAME_HEIGHT / 2 - exitYes.getCenterY());

	// exit NO button
	if (!exitNo.initialize(graphics, 0, 0, 0, &buttonsSmallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing exit button"));
	exitNo.setX(GAME_WIDTH / 1.5 - exitNo.getCenterX());
	exitNo.setY(GAME_HEIGHT / 2 - exitNo.getCenterY());

	//
	if (!confirmButton.initialize(graphics, 0, 0, 0, &buttonsSmallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing confirm button"));
	confirmButton.setX(GAME_WIDTH / 2 - confirmButton.getCenterX());
	confirmButton.setY(GAME_HEIGHT / 2 - confirmButton.getCenterY());

	// pause ui
	if (!pauseUI.initialize(graphics, 0, 0, 0, &pausedUITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause ui"));
	pauseUI.setX(GAME_WIDTH / 2 - pauseUI.getCenterX());
	pauseUI.setY(GAME_HEIGHT / 2 - pauseUI.getCenterY());

	//
	if (!achievementRequiredUI.initialize(graphics, 0, 0, 0, &achievementRequiredTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause ui"));
	achievementRequiredUI.setX(GAME_WIDTH / 2 - achievementRequiredUI.getCenterX());
	achievementRequiredUI.setY(GAME_HEIGHT / 2 - achievementRequiredUI.getCenterY());

	// win ui
	if (!winUI.initialize(graphics, 0, 0, 0, &winUITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player win ui"));
	winUI.setX(GAME_WIDTH / 2 - winUI.getCenterX());
	winUI.setY(GAME_HEIGHT / 2 - winUI.getCenterY());

	// exit ui
	if (!exitUI.initialize(graphics, 0, 0, 0, &exitUITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing exit ui"));
	exitUI.setX(GAME_WIDTH / 2 - exitUI.getCenterX());
	exitUI.setY(GAME_HEIGHT / 2 - exitUI.getCenterY());

	// background
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	/* for ai - enemy*/

	// enemy texture
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));

	// enemy image
	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
			
	// player
	player.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_END_FRAME);
	player.setCurrentFrame(playerNS::PLAYER_START_FRAME);
	player.setX(10);
	player.setY((GAME_HEIGHT - 49) - playerNS::HEIGHT);
	player.setVelocity(VECTOR2(-playerNS::INITIAL_SPEED, -playerNS::INITIAL_SPEED)); // VECTOR2(X, Y)
	
	/* for ai - enemy */
	// add the enemy to the scene
	/*enemy.setX(GAME_WIDTH / 2);
	enemy.setY((GAME_HEIGHT - 63) - enemyNS::HEIGHT);*/

	// tile & spike
	tile.setCurrentFrame(0);

	// initialize DirectX font for achievement
	if (dxAchievementFont.initialize(graphics, 30, false, false, "Courier New") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font for Achievement."));

	dxAchievementFont.setFontColor(graphicsNS::WHITE);
}

//=============================================================================
// Update all game items - updating every single thing that got changes
//=============================================================================
void AchievementQuest::update()
{
	float playerX = player.getX();
	int velocity = playerNS::XVELOCITY;

	if (menuOn && input->isKeyDown(ENTER_KEY))
	{
		menuOn = false;
		input->clearAll();
	}
	else
	{
		playerJumps = player.getJumpCount();
		player.update(frameTime);
	}

	//Scrolling Limiter
	//Left Screen
	if (mapX < 0)
	{
		mapX = 0;
	}
	//Right Screen
	else if (mapX > TILE_MAP_WIDTH * levelDesignNS::TEXTURE_SIZE - GAME_WIDTH / 4 * 3)
	{
		mapX = (TILE_MAP_WIDTH * levelDesignNS::TEXTURE_SIZE - GAME_WIDTH / 4 * 3);
	}

	//X Coord Scrolling
	if (playerX > GAME_WIDTH / 2 && (input->isKeyDown('D') || input->isKeyDown(VK_RIGHT)))
	{
		mapX += velocity * frameTime;  // scroll map right

		//If Map has not stopped moving, adjust the player's Coordinates to the previous location while it is scrolling
		if (mapX < TILE_MAP_WIDTH * levelDesignNS::TEXTURE_SIZE - GAME_WIDTH / 4 * 3)
		{
			player.setX((float)(playerX - velocity * frameTime));
			// enemy.setX((float)(enemy.getX() - velocity * frameTime));			
		}
		else
		{
			if (TotalAchievements == 15)
			{
				player.setScale(0);
				playerTile.setScale(0);
			}
			else
				player.setX(GAME_WIDTH / 2);
		}
	}
	else if (playerX < GAME_WIDTH / 2 && (input->isKeyDown('A') || input->isKeyDown(VK_LEFT)))
	{
		mapX -= velocity * frameTime;  // scroll map left

		//If Map has not stopped moving, adjust the player's Coordinates to the previous location while it is scrolling
		if (mapX > 0)
		{
			player.setX((float)(playerX + velocity * frameTime));
			// enemy.setX((float)(enemy.getX() + velocity * frameTime));
		}
	}

	if (input->isKeyDown('M'))
	{
		if (showMap == false)
		{
			showMap = true;
		}
		else if (showMap == true)
		{
			showMap = false;
		}
		input->clearKeyDown('M');
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void AchievementQuest::ai()
{}

//=============================================================================
// Handle collisions - checking collision detectioin of objects
//=============================================================================
void AchievementQuest::collisions()
{
	VECTOR2 collisionVector;
	VECTOR2 velo;
	velo.x = 0;
	velo.y = 0;
	bool collideTop = true;

	// collision between tiles/ spikes and player
	for (int row = 0; row < levelDesignNS::MAP_HEIGHT; row++)						// for each row of map
	{
		tile.setY((float)(row * levelDesignNS::TEXTURE_SIZE));						// set tile Y

		for (int col = 0; col < levelDesignNS::MAP_WIDTH; col++)					// for each column of map
		{
			if (levelDesignNS::tileMap[row][col] == 0)
			{
				tile.setX((float)(col * levelDesignNS::TEXTURE_SIZE) - mapX);		// set tile X

				// if tile on screen
				if (tile.getX() > -levelDesignNS::TEXTURE_SIZE && tile.getX() < GAME_WIDTH)
				{
					// jump down and land on the ground
					if (player.getVelocity().y >= 0 && player.collideBoxTop(tile, collisionVector))
					{
						player.setY(levelDesignNS::TEXTURE_SIZE * row - player.getHeight() * player.getScale());
						velo.y = 0;
						player.setVelocity(velo);
						player.allowJump();
						player.resetDoubleJump();
					}
					// jump up, hit the platform and land on the ground
					else if (player.collidesWith(tile, collisionVector))
					{
						velo.y = +10;
						player.setVelocity(velo);
					}
					// in contact with the platform when moving right
					else if (player.collideBoxLeft(tile, collisionVector))
					{
						velo.x = -playerNS::XVELOCITY;
						player.setVelocity(velo);
					}
					// in contact with the platform when moving left
					else if (player.collideBoxRight(tile, collisionVector))
					{
						velo.x = playerNS::XVELOCITY;
						player.setVelocity(velo);
					}
				}
			}
			// if spike is present
			if ((levelDesignNS::tileMap[row][col] >= 1 && levelDesignNS::tileMap[row][col] <= 5))
			{
				tile.setX((float)(col * levelDesignNS::TEXTURE_SIZE) - mapX);		// set tile X

				// collision between spike and player - player disappears and spawn a new character at the starting point
				if (player.collidesWith(tile, collisionVector) || (player.collidesWith(enemy,collisionVector)) && TotalAchievements <= 5)
				{
					playerDeath++;

					if ((col > 0 && col < 29)) 
						mapX = 0;									// first room map start point
					if (col > 30 && col < 54)
						mapX = 26 * levelDesignNS::TEXTURE_SIZE;	// second room map start point
					if (col > 60 && col < levelDesignNS::MAP_WIDTH)
						mapX = 56 * levelDesignNS::TEXTURE_SIZE;	// third room map start point

					player.setX(levelDesignNS::TEXTURE_SIZE);
					player.resetDoubleJump();
				}
				else if (player.collidesWith(enemy,collisionVector) && TotalAchievements > 5)
				{
					enemy.setScale(0);
					monsterKills++;
				}
			}
		}
	}
}

//=============================================================================
// Render game items - drawing
//=============================================================================
void AchievementQuest::render()
{
	graphics->spriteBegin();										// begin drawing sprites

	if (TotalAchievements < 15 && mapX == TILE_MAP_WIDTH * levelDesignNS::TEXTURE_SIZE - GAME_WIDTH / 4 * 3)
	{
		achievementRequired = true;
	}

	// game paused upon escape key press
	else if (input->wasKeyPressed(VK_ESCAPE))
	{
		if (paused == false)
			paused = true;
		else
			paused = false;
	}
	// player wins
	else if (TotalAchievements == 15 && mapX >= TILE_MAP_WIDTH * levelDesignNS::TEXTURE_SIZE - GAME_WIDTH / 4 * 3)
	{
		playerWin = true;
	}

	
	if (menuOn)
		menu.draw();
	else
	{
		background.draw();
		player.draw();						// add the player to the scene
		enemy.draw();

		// add the tiles & spikes to the scene
		for (int row = 0; row < levelDesignNS::MAP_HEIGHT; row++)						// for each row of map
		{
			tile.setY((float)(row * levelDesignNS::TEXTURE_SIZE));						// set tile Y
			for (int col = 0; col < levelDesignNS::MAP_WIDTH; col++)					// for each column of map
			{
				if (levelDesignNS::tileMap[row][col] >= 0)								// if tile present
				{
					tile.setCurrentFrame(levelDesignNS::tileMap[row][col]);				// set tile texture
					tile.setX((float)(col * levelDesignNS::TEXTURE_SIZE) - mapX);		// set tile X

					// if tile on screen
					//if (tile.getX() > -levelDesignNS::TEXTURE_SIZE && tile.getX() < GAME_WIDTH)
					tile.draw();									// draw tile
				}
			}
		}

		//Show Minimap
		if (showMap == true)
		{
			int maxTileX = (player.getX() + mapX) / levelDesignNS::TEXTURE_SIZE + 8;

			if (maxTileX > levelDesignNS::MAP_WIDTH)
			{
				maxTileX = levelDesignNS::MAP_WIDTH;
			}

			// add the tiles & spikes to the minimap
			for (int row = 0; row < levelDesignNS::MAP_HEIGHT; row++)						// for each row of map
			{
				miniTile.setY((float)(row * levelDesignNS::MINIMAP_TEXTURE_SIZE));						// set tile Y
				for (int col = 0; col < maxTileX; col++)					// for each column of map
				{
					if (levelDesignNS::tileMap[row][col] >= 0)								// if tile present
					{
						miniTile.setCurrentFrame(levelDesignNS::tileMap[row][col]);				// set tile texture
						miniTile.setX((float)((col - (mapX / levelDesignNS::TEXTURE_SIZE))* levelDesignNS::MINIMAP_TEXTURE_SIZE));    // set tile X 

					}
					// if tile on screen
					miniTile.draw();									// draw tile
				}

			}
			//get player coords
			float locationX = player.getX() / levelDesignNS::TEXTURE_SIZE;
			float locationY = player.getY() / levelDesignNS::TEXTURE_SIZE;
			playerTile.setX((float)(locationX * levelDesignNS::MINIMAP_TEXTURE_SIZE)); //set miniPlayer X coord
			playerTile.setY((float)(locationY * levelDesignNS::MINIMAP_TEXTURE_SIZE)); //set miniPlayer Y coord
			playerTile.draw(); //draw miniPlayer on minimap

			if (locationX > levelDesignNS::MAP_WIDTH)
				playerTile.setScale(0);
		}

		ui.draw();

		for (int i = 0; i< 15 /*NEED TO CHANGE*/; i++)
		{
			dxAchievementFont.print(achievementList[i]->getAchievement(&playerDeath, &playerJumps, &monsterKills), GAME_WIDTH * 0.78, GAME_HEIGHT - 70 - (i * 45));
			achievementPlaceholder += achievementList[i]->getFlag();
		}
		TotalAchievements = achievementPlaceholder;

		dxAchievementFont.print("Achievements: " + to_string(TotalAchievements), 5/*GAME_WIDTH*/, GAME_HEIGHT - 30);
		dxAchievementFont.print("Jumps: " + to_string(playerJumps), 300/*GAME_WIDTH*/, GAME_HEIGHT - 30);
		dxAchievementFont.print("Deaths: " + to_string(playerDeath), 500/*GAME_WIDTH*/, GAME_HEIGHT - 30);
		// Reset the count
		achievementPlaceholder = 0;

		if (exitConfirmation == true)
		{
			if (paused == true)
				pauseUI.draw();
			else if (playerWin == true)
				winUI.draw();

			exitUI.draw();

			exitYes.draw();
			dxAchievementFont.print("Yes", exitYes.getX() + 25, exitYes.getY() + 10);

			exitNo.draw();
			dxAchievementFont.print("No", exitNo.getX() + 35, exitNo.getY() + 10);

			if (input->getMouseLButton()) // checks for mouse clicks when the pause menu is shown
			{
				if ((input->getMouseX() > exitYes.getX()) && (input->getMouseX() < (exitYes.getX() + exitYes.getWidth()))
					&& (input->getMouseY() > exitYes.getY()) && input->getMouseY() < exitYes.getY() + exitYes.getHeight())
					PostQuitMessage(0);

				else if ((input->getMouseX() > exitNo.getX()) && (input->getMouseX() < (exitNo.getX() + exitNo.getWidth()))
					&& (input->getMouseY() > exitNo.getY()) && input->getMouseY() < exitNo.getY() + exitNo.getHeight())
					// shoot to menu
					// DK how to code LOL
					exitConfirmation = false;
			}
		}

		else if (paused == true)
		{
			pauseUI.draw();

			resumeButton.draw();
			dxAchievementFont.print("Resume", resumeButton.getX() + 47, resumeButton.getY() + 10);

			mainMenuButton.draw();
			dxAchievementFont.print("Main Menu", mainMenuButton.getX() + 30, mainMenuButton.getY() + 10);

			exitButton.draw();
			dxAchievementFont.print("Exit", exitButton.getX() + 65, exitButton.getY() + 10);

			if (input->getMouseLButton()) // checks for mouse clicks when the pause menu is shown
			{
				if ((input->getMouseX() > resumeButton.getX()) && (input->getMouseX() < (resumeButton.getX() + resumeButton.getWidth()))
					&& (input->getMouseY() > resumeButton.getY()) && input->getMouseY() < resumeButton.getY() + resumeButton.getHeight())
					paused = false; // resume the game

				else if ((input->getMouseX() > mainMenuButton.getX()) && (input->getMouseX() < (mainMenuButton.getX() + mainMenuButton.getWidth()))
					&& (input->getMouseY() > mainMenuButton.getY()) && input->getMouseY() < mainMenuButton.getY() + mainMenuButton.getHeight())
					// shoot to menu
					// DK how to code LOL
					restartGame();

				else if ((input->getMouseX() > exitButton.getX()) && (input->getMouseX() < (exitButton.getX() + exitButton.getWidth()))
					&& (input->getMouseY() > exitButton.getY()) && input->getMouseY() < exitButton.getY() + exitButton.getHeight())
					exitConfirmation = true;
			}
		}
		else if (achievementRequired == true)
		{
			achievementRequiredUI.draw();

			confirmButton.draw();
			dxAchievementFont.print("Ok", confirmButton.getX() + 25, confirmButton.getY() + 10);

			if (input->getMouseLButton()) // checks for mouse clicks when the pause menu is shown
			{
				if ((input->getMouseX() > confirmButton.getX()) && (input->getMouseX() < (confirmButton.getX() + confirmButton.getWidth()))
					&& (input->getMouseY() > confirmButton.getY()) && input->getMouseY() < confirmButton.getY() + confirmButton.getHeight())
				{
					player.setX(player.getX() - 32);
					achievementRequired = false;
				}
			}
		}
		else if (playerWin == true)
		{
			winUI.draw();

			mainMenuButton.draw();
			dxAchievementFont.print("Main Menu", mainMenuButton.getX() + 30, mainMenuButton.getY() + 10);

			exitButton.draw();
			dxAchievementFont.print("Exit", exitButton.getX() + 65, exitButton.getY() + 10);

			if (input->getMouseLButton()) // checks for mouse clicks when the pause menu is shown
			{
				if ((input->getMouseX() > mainMenuButton.getX()) && (input->getMouseX() < (mainMenuButton.getX() + mainMenuButton.getWidth()))
					&& (input->getMouseY() > mainMenuButton.getY()) && input->getMouseY() < mainMenuButton.getY() + mainMenuButton.getHeight())
					// shoot to menu
					restartGame();

				else if ((input->getMouseX() > exitButton.getX()) && (input->getMouseX() < (exitButton.getX() + exitButton.getWidth()))
					&& (input->getMouseY() > exitButton.getY()) && input->getMouseY() < exitButton.getY() + exitButton.getHeight())
					exitConfirmation = true;
			}
		}
	}
	graphics->spriteEnd();											// end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void AchievementQuest::releaseAll()
{
	playerTexture.onLostDevice();
	tileTexture.onLostDevice();
	menuTexture.onLostDevice();
	uiTexture.onLostDevice();
	pausedUITexture.onLostDevice();
	exitUITexture.onLostDevice();
	buttonsTexture.onLostDevice();
	buttonsSmallTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	miniPlayerTexture.onLostDevice();
	miniTileTexture.onLostDevice();
	winUITexture.onLostDevice();
	achievementRequiredTexture.onLostDevice();

	/* for ai - enemy */
	enemyTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void AchievementQuest::resetAll()
{
	playerTexture.onResetDevice();
	tileTexture.onResetDevice();
	menuTexture.onResetDevice();
	uiTexture.onResetDevice();
	buttonsTexture.onResetDevice();
	pausedUITexture.onResetDevice();
	exitUITexture.onResetDevice();
	buttonsSmallTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	miniPlayerTexture.onResetDevice();
	miniTileTexture.onResetDevice();
	winUITexture.onResetDevice();
	achievementRequiredTexture.onResetDevice();

	/* for ai - enemy */
	enemyTexture.onResetDevice();

	Game::resetAll();
	return;
}

//=============================================================================
// The game has been restarted.
//=============================================================================
void AchievementQuest::restartGame()
{
	playerDeath = 0;
	TotalAchievements = 0;
	achievementPlaceholder = 0;

	player.resetJumps();
	player.setX(35);
	player.setY((GAME_HEIGHT - 49) - playerNS::HEIGHT);

	enemy.setY(640);
	enemy.setY((GAME_HEIGHT - 49) - enemyNS::HEIGHT);

	menuOn = true;
	paused = false;
	playerWin = false;
	achievementRequired = false;

	for (int i = 0; i < 15; i++)
	{
		achievementList[i]->resetFlag();
	}

	mapX = 0;
}