/* ================================================================
BOSS SAINT & FLASH PROJECTILE UPDATE
================================================================ */
if (bossSaint.active && bossSaint.alive) {
	if (bossSaint.isEntering) {
		bossSaint.x -= 5.2;
		bossSaint.walkTimer++;
		if (bossSaint.walkTimer > 4) {
			bossSaint.walkFrame = (bossSaint.walkFrame + 1) % 4;
			bossSaint.walkTimer = 0;
		}
		if (bossSaint.x <= SCREEN_W - 320) {
			bossSaint.x = SCREEN_W - 320;
			bossSaint.isEntering = false;
		}
	}
	else if (!levelDone) {
		double dist = bossSaint.x - charX;

		bossSaint.flashCooldown++;
		if (bossSaint.flashCooldown >= 80 && !bossFlash.active && dist > 160.0) {
			bossFlash.active = true;
			bossFlash.x = bossSaint.x - 30;
			bossFlash.y = GROUND_Y + 70;
			bossFlash.speed = 10.0;
			bossSaint.flashCooldown = 0;
			bossSaint.isFighting = true;
			bossSaint.fightFrame = 1;
		}

		if (dist <= 150.0 && dist >= -50.0) {
			bossSaint.isFighting = true;
			bossSaint.fightTimer++;
			if (bossSaint.fightTimer > 4) {
				bossSaint.fightFrame = (bossSaint.fightFrame + 1) % 4;
				bossSaint.fightTimer = 0;
			}

			bossSaint.attackCooldown++;
			if (bossSaint.attackCooldown >= 16) {
				playerHealth -= 15;
				if (playerHealth < 0) playerHealth = 0;
				bossSaint.attackCooldown = 0;
			}
		}
		else {
			bossSaint.isFighting = false;
			bossSaint.walkTimer++;
			if (bossSaint.walkTimer > 4) {
				bossSaint.walkFrame = (bossSaint.walkFrame + 1) % 4;
				bossSaint.walkTimer = 0;
			}

			if (dist > 150.0) {
				bossSaint.x -= 4.8;
			}
			else if (dist < 80.0) {
				bossSaint.x += 4.8;
			}
		}
	}
}

// Update Flash projectile
if (bossFlash.active) {
	bossFlash.x -= bossFlash.speed;

	if ((currentState == FIGHT_RIGHT || currentState == FIGHT_LEFT)) {
		if (bossFlash.x >= charX + 20 && bossFlash.x <= charX + 240) {
			bossFlash.active = false;
		}
	}

	if (bossFlash.active && bossFlash.x <= charX + 110 && bossFlash.x >= charX - 30) {
		playerHealth -= 15;
		if (playerHealth < 0) playerHealth = 0;
		bossFlash.active = false;
	}

	if (bossFlash.x < -100) {
		bossFlash.active = false;
	}
}

/* ================================================================
BOSS MESH (KING / MAIN VILLAIN - LEVEL 4) UPDATE
================================================================ */
if (bossMesh.active && bossMesh.alive) {
	if (bossMesh.isEntering) {
		bossMesh.x -= 4.5;
		bossMesh.walkTimer++;
		if (bossMesh.walkTimer > 4) {
			bossMesh.walkFrame = (bossMesh.walkFrame + 1) % 5;
			bossMesh.walkTimer = 0;
		}
		double entranceStopX = SCREEN_W - 320.0;
		if (entranceStopX < charX + 210.0) entranceStopX = charX + 210.0;
		if (bossMesh.x <= entranceStopX) {
			bossMesh.x = entranceStopX;
			bossMesh.isEntering = false;
		}
	}
	else if (!levelDone) {
		// Determine facing direction relative to Hero
		bossMesh.fromRight = (bossMesh.x >= charX);

		if (bossMesh.fromRight) {
			// Mesh is on the RIGHT side of Hero: Maintain strict combat safety gap
			double targetX = charX + 210.0;
			if (targetX > SCREEN_W - 200.0) targetX = SCREEN_W - 200.0;

			double distToTarget = bossMesh.x - targetX;

			if (distToTarget > 4.5) {
				// Move left towards Hero, stopping strictly at targetX
				bossMesh.x -= 4.2;
				if (bossMesh.x < targetX) bossMesh.x = targetX;
				bossMesh.isFighting = false;
				bossMesh.walkTimer++;
				if (bossMesh.walkTimer > 4) {
					bossMesh.walkFrame = (bossMesh.walkFrame + 1) % 5;
					bossMesh.walkTimer = 0;
				}
			}
			else if (distToTarget < -4.5) {
				// If closer than minimum distance, step back right to targetX
				bossMesh.x += 4.2;
				if (bossMesh.x > targetX) bossMesh.x = targetX;
				bossMesh.isFighting = false;
				bossMesh.walkTimer++;
				if (bossMesh.walkTimer > 4) {
					bossMesh.walkFrame = (bossMesh.walkFrame + 1) % 5;
					bossMesh.walkTimer = 0;
				}
			}
			else {
				// At exact combat distance
				bossMesh.x = targetX;
				bossMesh.isFighting = true;
				bossMesh.fightTimer++;
				if (bossMesh.fightTimer > 4) {
					bossMesh.fightFrame = (bossMesh.fightFrame + 1) % 5;
					bossMesh.fightTimer = 0;
				}

				bossMesh.attackCooldown++;
				if (bossMesh.attackCooldown >= 18) {
					playerHealth -= 15;
					if (playerHealth < 0) playerHealth = 0;
					bossMesh.attackCooldown = 0;
				}
			}
		}
		else {
			// Mesh is on the LEFT side of Hero: Maintain strict combat safety gap
			double targetX = charX - 220.0;
			if (targetX < 40.0) targetX = 40.0;

			double distToTarget = targetX - bossMesh.x;

			if (distToTarget > 4.5) {
				// Move right towards Hero, stopping strictly at targetX
				bossMesh.x += 4.2;
				if (bossMesh.x > targetX) bossMesh.x = targetX;
				bossMesh.isFighting = false;
				bossMesh.walkTimer++;
				if (bossMesh.walkTimer > 4) {
					bossMesh.walkFrame = (bossMesh.walkFrame + 1) % 5;
					bossMesh.walkTimer = 0;
				}
			}
			else if (distToTarget < -4.5) {
				// If closer than minimum distance, step back left to targetX
				bossMesh.x -= 4.2;
				if (bossMesh.x < targetX) bossMesh.x = targetX;
				bossMesh.isFighting = false;
				bossMesh.walkTimer++;
				if (bossMesh.walkTimer > 4) {
					bossMesh.walkFrame = (bossMesh.walkFrame + 1) % 5;
					bossMesh.walkTimer = 0;
				}
			}
			else {
				// At exact combat distance
				bossMesh.x = targetX;
				bossMesh.isFighting = true;
				bossMesh.fightTimer++;
				if (bossMesh.fightTimer > 4) {
					bossMesh.fightFrame = (bossMesh.fightFrame + 1) % 5;
					bossMesh.fightTimer = 0;
				}

				bossMesh.attackCooldown++;
				if (bossMesh.attackCooldown >= 18) {
					playerHealth -= 15;
					if (playerHealth < 0) playerHealth = 0;
					bossMesh.attackCooldown = 0;
				}
			}
		}
	}
}
}



void iDraw()
{
	iClear();
	if (currentScreen == SCREEN_SPLASH)   { drawSplash();  return; }
	if (currentScreen == SCREEN_MENU)     { drawMenu();    return; }
	if (currentScreen == SCREEN_OPTIONS)  { drawOptions(); return; }
	if (currentScreen == SCREEN_STORY)    { drawStory();   return; }
	if (currentScreen == SCREEN_END_CARD) { drawEndCard(); return; }
	if (currentScreen == SCREEN_CREDITS)  { drawCredits(); return; }
	drawGame();
}

/* ================================================================
INPUT HANDLERS
================================================================ */
void exitGame()
{
	gSaveSystem.clearAllData();
	gAudio.shutdown();
	exit(0);
}

void iKeyboard(unsigned char key)
{
	// 1. If Name Input modal is active, process all typed characters (including 'h', 'f', Enter, Backspace, Esc)
	if (isNamingPlayer) {
		if (key == 13 || key == '\r' || key == '\n') {
			if (nameInputLen == 0) {
				strcpy_s(nameInputBuffer, sizeof(nameInputBuffer), "Hero");
				nameInputLen = (int)strlen(nameInputBuffer);
			}
			if (currentScreen == SCREEN_MENU) {
				gSaveSystem.addNewPlayer(nameInputBuffer);
				isNamingPlayer = false;
				currentScreen = SCREEN_STORY;
				storyIndex = 1;
				selectedLevelToStart = 0;
				return;
			}
			else if (currentScreen == SCREEN_OPTIONS) {
				if (selectedLevelToStart > 0) {
					gSaveSystem.addNewPlayer(nameInputBuffer);
					isNamingPlayer = false;
					int lvl = selectedLevelToStart;
					selectedLevelToStart = 0;
					startLevel(lvl);
					return;
				}
				else {
					if (namingTargetSlot == -1) {
						gSaveSystem.addNewPlayer(nameInputBuffer);
						optionsPlayerPage = gSaveSystem.getActivePlayerIndex() / 3;
					}
					else if (namingTargetSlot >= 0 && namingTargetSlot < gSaveSystem.getNumPlayers()) {
						gSaveSystem.setPlayerName(namingTargetSlot, nameInputBuffer);
					}
					isNamingPlayer = false;
					return;
				}
			}
		}
		if (key == 27) { // ESC cancels modal
			isNamingPlayer = false;
			selectedLevelToStart = 0;
			return;
		}
		if (key == '\b' || key == 8) { // Backspace
			if (nameInputLen > 0) {
				nameInputLen--;
				nameInputBuffer[nameInputLen] = '\0';
			}
			return;
		}
		if (key >= 32 && key <= 126) { // Any printable ASCII characters
			if (nameInputLen < 24) {
				nameInputBuffer[nameInputLen++] = (char)key;
				nameInputBuffer[nameInputLen] = '\0';
			}
			return;
		}
		return;
	}

	if (key == 27) {
		if (currentScreen == SCREEN_OPTIONS || currentScreen == SCREEN_CREDITS) {
			currentScreen = SCREEN_MENU;
			return;
		}
		exitGame();
	}

	if (key == 'f' || key == 'F') {
		iToggleFullScreen();
		return;
	}

	if (key == 'h' || key == 'H') {
		currentScreen = SCREEN_MENU;
		isNamingPlayer = false;
		showWinCard = false;
		levelDone = false;
		isEntering = false;
		isExiting = false;
		isPaused = false;
		optionsPlayerPage = 0;
		gAudio.playMenuBGM();
		return;
	}

	if (currentScreen == SCREEN_SPLASH) {
		if (key == 13 || key == '\r') {
			currentScreen = SCREEN_MENU;
			gAudio.playMenuBGM();
		}
		return;
	}

	if (currentScreen == SCREEN_MENU) {
		if (key == 'o' || key == 'O') {
			currentScreen = SCREEN_OPTIONS;
			return;
		}
		if (key == 'c' || key == 'C') {
			currentScreen = SCREEN_CREDITS;
			return;
		}
		if (key == 13 || key == '\r' || key == ' ') {
			isNamingPlayer = true;
			namingTargetSlot = -1;
			nameInputBuffer[0] = '\0';
			nameInputLen = 0;
			return;
		}
		return;
	}

	if (currentScreen == SCREEN_OPTIONS) {
		if (key == 'r' || key == 'R' || key == 'e' || key == 'E') {
			isNamingPlayer = true;
			namingTargetSlot = gSaveSystem.getActivePlayerIndex();
			strcpy_s(nameInputBuffer, sizeof(nameInputBuffer), gSaveSystem.getActivePlayer().name);
			nameInputLen = strlen(nameInputBuffer);
			return;
		}
		if (key == 'm' || key == 'M') {
			gAudio.toggleMusic();
			gSaveSystem.setMusicEnabled(gAudio.isMusicEnabled());
			return;
		}
		if (key == 's' || key == 'S') {
			gAudio.toggleSound();
			gSaveSystem.setSoundEnabled(gAudio.isSoundEnabled());
			return;
		}
		if (key == 'n' || key == 'N' || key == '+' || key == '=') {
			if (gSaveSystem.getNumPlayers() < MAX_SAVED_PLAYERS) {
				isNamingPlayer = true;
				namingTargetSlot = -1; // New player mode
				nameInputBuffer[0] = '\0';
				nameInputLen = 0;
			}
			return;
		}
		if (key == '[' || key == '<' || key == ',') {
			if (optionsPlayerPage > 0) optionsPlayerPage--;
			return;
		}
		if (key == ']' || key == '>' || key == '.') {
			if ((optionsPlayerPage + 1) * 3 < gSaveSystem.getNumPlayers()) {
				optionsPlayerPage++;
			}
			return;
		}
		int startIdx = optionsPlayerPage * 3;
		if (key == '1') {
			if (startIdx < gSaveSystem.getNumPlayers()) gSaveSystem.setActivePlayerIndex(startIdx);
			return;
		}
		if (key == '2') {
			if (startIdx + 1 < gSaveSystem.getNumPlayers()) gSaveSystem.setActivePlayerIndex(startIdx + 1);
			return;
		}
		if (key == '3') {
			if (startIdx + 2 < gSaveSystem.getNumPlayers()) gSaveSystem.setActivePlayerIndex(startIdx + 2);
			return;
		}
		if (key == 'b' || key == 'B' || key == ' ' || key == 27) {
			currentScreen = SCREEN_MENU;
			return;
		}
		return;
	}

	if (currentScreen == SCREEN_STORY) {
		if (key == 's' || key == 'S') {
			skipStory();
			return;
		}
		if (key == 'n' || key == 'N' || key == 13 || key == '\r' || key == ' ') {
			advanceStory();
			return;
		}
		return;
	}

	if (currentScreen == SCREEN_END_CARD) {
		if (key == 'h' || key == 'H' || key == 13 || key == '\r' || key == ' ') {
			currentScreen = SCREEN_MENU;
			isNamingPlayer = false;
			showWinCard = false;
			levelDone = false;
			isEntering = false;
			isExiting = false;
			isPaused = false;
			optionsPlayerPage = 0;
			gAudio.playMenuBGM();
		}
		return;
	}

	if (currentScreen == SCREEN_CREDITS) {
		if (key == 'b' || key == 'B' || key == 13 || key == '\r' || key == ' ' || key == 27) {
			currentScreen = SCREEN_MENU;
		}
		return;
	}

	if (key == 'r' || key == 'R') {
		restartGame();
		return;
	}

	if (showWinCard) {
		if (key == 'n' || key == 'N' || key == 13 || key == '\r' || key == ' ') {
			if (currentLevel == 1) {
				startLevel(2);
			}
			else if (currentLevel == 2) {
				startLevel(3);
			}
			else if (currentLevel == 3) {
				startLevel(4);
			}
			else if (currentLevel == 4) {
				currentScreen = SCREEN_END_CARD;
			}
			return;
		}
	}

	if (key == ' ') {
		isPaused = !isPaused;
		return;
	}

	if (isPaused) return;

	if (key == 'n' || key == 'N') {
		if (currentLevel == 3 && nCooldown >= 1.0) {
			castNPower();
		}
	}
	else if (key == 'd' || key == 'D') {
		moveRight();
	}
	else if (key == 'm' || key == 'M') {
		if (currentLevel == 3) {
			castMPower();
		}
	}
	else if (key == 'a' || key == 'A') moveLeft();
	else if (key == 'w' || key == 'W') jump();
	else if (key == 's' || key == 'S') sit();
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_F11) {
		iToggleFullScreen();
		return;
	}

	if (currentScreen == SCREEN_STORY) {
		if (key == GLUT_KEY_RIGHT) {
			advanceStory();
			return;
		}
	}

	if (currentScreen != SCREEN_GAME) return;

	if (showWinCard) {
		if (key == GLUT_KEY_RIGHT) {
			if (currentLevel == 1) {
				startLevel(2);
			}
			else if (currentLevel == 2) {
				startLevel(3);
			}
			else if (currentLevel == 3) {
				startLevel(4);
			}
			else if (currentLevel == 4) {
				currentScreen = SCREEN_END_CARD;
			}
			return;
		}
	}

	if (isPaused) return;

	if (key == GLUT_KEY_RIGHT) moveRight();
	else if (key == GLUT_KEY_LEFT) moveLeft();
	else if (key == GLUT_KEY_UP) jump();
	else if (key == GLUT_KEY_DOWN) sit();
}

void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isAttackButtonHeld = false;
		return;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isAttackButtonHeld = true;

		if (currentScreen == SCREEN_SPLASH) {
			currentScreen = SCREEN_MENU;
			gAudio.playMenuBGM();
			return;
		}

		if (currentScreen == SCREEN_MENU) {
			if (isNamingPlayer) {
				// Confirm Button in modal -> Start Game
				if (mx >= BTN_MODAL_CONFIRM_X1 && mx <= BTN_MODAL_CONFIRM_X2 &&
					my >= BTN_MODAL_CONFIRM_Y1 && my <= BTN_MODAL_CONFIRM_Y2) {
					if (nameInputLen == 0) {
						strcpy_s(nameInputBuffer, sizeof(nameInputBuffer), "Hero");
						nameInputLen = (int)strlen(nameInputBuffer);
					}
					gSaveSystem.addNewPlayer(nameInputBuffer);
					isNamingPlayer = false;
					selectedLevelToStart = 0;
					currentScreen = SCREEN_STORY;
					storyIndex = 1;
					return;
				}

				// Cancel Button in modal
				if (mx >= BTN_MODAL_CANCEL_X1 && mx <= BTN_MODAL_CANCEL_X2 &&
					my >= BTN_MODAL_CANCEL_Y1 && my <= BTN_MODAL_CANCEL_Y2) {
					isNamingPlayer = false;
					selectedLevelToStart = 0;
					return;
				}

				// If clicked inside modal window, consume click
				if (mx >= 300 && mx <= 980 && my >= 140 && my <= 560) {
					return;
				}

				// Click outside modal cancels
				isNamingPlayer = false;
				selectedLevelToStart = 0;
				return;
			}

			// Start Game Button -> Opens Name Input Modal
			if (mx >= BTN_START_X1 && mx <= BTN_START_X2 &&
				my >= BTN_START_Y1 && my <= BTN_START_Y2) {
				selectedLevelToStart = 1;
				isNamingPlayer = true;
				namingTargetSlot = -2;
				nameInputBuffer[0] = '\0';
				nameInputLen = 0;
				return;
			}

			// Options Button
			if (mx >= BTN_OPTIONS_X1 && mx <= BTN_OPTIONS_X2 &&
				my >= BTN_OPTIONS_Y1 && my <= BTN_OPTIONS_Y2) {
				currentScreen = SCREEN_OPTIONS;
				return;
			}

			// Credits Button
			if (mx >= BTN_CREDITS_X1 && mx <= BTN_CREDITS_X2 &&
				my >= BTN_CREDITS_Y1 && my <= BTN_CREDITS_Y2) {
				currentScreen = SCREEN_CREDITS;
				return;
			}

			// Exit Button
			if (mx >= BTN_EXIT_X1 && mx <= BTN_EXIT_X2 &&
				my >= BTN_EXIT_Y1 && my <= BTN_EXIT_Y2) {
				exitGame();
			}
			return;
		}

		if (currentScreen == SCREEN_OPTIONS) {
			if (isNamingPlayer) {
				// Confirm Button in modal
				if (mx >= BTN_MODAL_CONFIRM_X1 && mx <= BTN_MODAL_CONFIRM_X2 &&
					my >= BTN_MODAL_CONFIRM_Y1 && my <= BTN_MODAL_CONFIRM_Y2) {
					if (nameInputLen == 0) {
						strcpy_s(nameInputBuffer, sizeof(nameInputBuffer), "Hero");
						nameInputLen = (int)strlen(nameInputBuffer);
					}
					if (selectedLevelToStart > 0) {
						gSaveSystem.addNewPlayer(nameInputBuffer);
						isNamingPlayer = false;
						int lvl = selectedLevelToStart;
						selectedLevelToStart = 0;
						startLevel(lvl);
						return;
					}
					else {
						if (namingTargetSlot == -1) {
							gSaveSystem.addNewPlayer(nameInputBuffer);
							optionsPlayerPage = gSaveSystem.getActivePlayerIndex() / 3;
						}
						else if (namingTargetSlot >= 0 && namingTargetSlot < gSaveSystem.getNumPlayers()) {
							gSaveSystem.setPlayerName(namingTargetSlot, nameInputBuffer);
						}
						isNamingPlayer = false;
						return;
					}
				}

				// Cancel Button in modal
				if (mx >= BTN_MODAL_CANCEL_X1 && mx <= BTN_MODAL_CANCEL_X2 &&
					my >= BTN_MODAL_CANCEL_Y1 && my <= BTN_MODAL_CANCEL_Y2) {
					isNamingPlayer = false;
					selectedLevelToStart = 0;
					return;
				}

				// If clicked inside modal window, consume click
				if (mx >= 300 && mx <= 980 && my >= 140 && my <= 560) {
					return;
				}

				// Click outside modal cancels
				isNamingPlayer = false;
				selectedLevelToStart = 0;
				return;
			}

			// Level 1 Select Button
			if (mx >= BTN_OPT_LVL1_X1 && mx <= BTN_OPT_LVL1_X2 &&
				my >= BTN_OPT_LVL1_Y1 && my <= BTN_OPT_LVL1_Y2) {
				selectedLevelToStart = 1;
				isNamingPlayer = true;
				namingTargetSlot = -2;
				nameInputBuffer[0] = '\0';
				nameInputLen = 0;
				return;
			}

			// Level 2 Select Button
			if (mx >= BTN_OPT_LVL2_X1 && mx <= BTN_OPT_LVL2_X2 &&
				my >= BTN_OPT_LVL2_Y1 && my <= BTN_OPT_LVL2_Y2) {
				selectedLevelToStart = 2;
				isNamingPlayer = true;
				namingTargetSlot = -2;
				nameInputBuffer[0] = '\0';
				nameInputLen = 0;
				return;
			}

			// Level 3 Select Button
			if (mx >= BTN_OPT_LVL3_X1 && mx <= BTN_OPT_LVL3_X2 &&
				my >= BTN_OPT_LVL3_Y1 && my <= BTN_OPT_LVL3_Y2) {
				selectedLevelToStart = 3;
				isNamingPlayer = true;
				namingTargetSlot = -2;
				nameInputBuffer[0] = '\0';
				nameInputLen = 0;
				return;
			}

			// Level 4 Select Button
			if (mx >= BTN_OPT_LVL4_X1 && mx <= BTN_OPT_LVL4_X2 &&
				my >= BTN_OPT_LVL4_Y1 && my <= BTN_OPT_LVL4_Y2) {
				selectedLevelToStart = 4;
				isNamingPlayer = true;
				namingTargetSlot = -2;
				nameInputBuffer[0] = '\0';
				nameInputLen = 0;
				return;
			}

			// Rename Active Player Button
			if (mx >= BTN_OPT_RENAME_X1 && mx <= BTN_OPT_RENAME_X2 &&
				my >= BTN_OPT_RENAME_Y1 && my <= BTN_OPT_RENAME_Y2) {
				selectedLevelToStart = 0;
				isNamingPlayer = true;
				namingTargetSlot = gSaveSystem.getActivePlayerIndex();
				strcpy_s(nameInputBuffer, sizeof(nameInputBuffer), gSaveSystem.getActivePlayer().name);
				nameInputLen = strlen(nameInputBuffer);
				return;
			}

			// Music Toggle
			if (mx >= BTN_OPT_MUSIC_X1 && mx <= BTN_OPT_MUSIC_X2 &&
				my >= BTN_OPT_MUSIC_Y1 && my <= BTN_OPT_MUSIC_Y2) {
				gAudio.toggleMusic();
				gSaveSystem.setMusicEnabled(gAudio.isMusicEnabled());
				return;
			}

			// Sound Toggle
			if (mx >= BTN_OPT_SOUND_X1 && mx <= BTN_OPT_SOUND_X2 &&
				my >= BTN_OPT_SOUND_Y1 && my <= BTN_OPT_SOUND_Y2) {
				gAudio.toggleSound();
				gSaveSystem.setSoundEnabled(gAudio.isSoundEnabled());
				return;
			}

			// Prev Page Button
			if (mx >= BTN_OPT_PREV_X1 && mx <= BTN_OPT_PREV_X2 &&
				my >= BTN_OPT_PREV_Y1 && my <= BTN_OPT_PREV_Y2) {
				if (optionsPlayerPage > 0) optionsPlayerPage--;
				return;
			}

			// Next Page Button
			if (mx >= BTN_OPT_NEXT_X1 && mx <= BTN_OPT_NEXT_X2 &&
				my >= BTN_OPT_NEXT_Y1 && my <= BTN_OPT_NEXT_Y2) {
				if ((optionsPlayerPage + 1) * 3 < gSaveSystem.getNumPlayers()) {
					optionsPlayerPage++;
				}
				return;
			}

			// Add New Player Button
			if (mx >= BTN_OPT_ADD_X1 && mx <= BTN_OPT_ADD_X2 &&
				my >= BTN_OPT_ADD_Y1 && my <= BTN_OPT_ADD_Y2) {
				if (gSaveSystem.getNumPlayers() < MAX_SAVED_PLAYERS) {
					selectedLevelToStart = 0;
					isNamingPlayer = true;
					namingTargetSlot = -1; // New player mode
					nameInputBuffer[0] = '\0';
					nameInputLen = 0;
				}
				return;
			}

			int startIdx = optionsPlayerPage * 3;

			// Slot 1
			if (mx >= BTN_OPT_P1_X1 && mx <= BTN_OPT_P1_X2 &&
				my >= BTN_OPT_P1_Y1 && my <= BTN_OPT_P1_Y2) {
				if (startIdx < gSaveSystem.getNumPlayers()) {
					gSaveSystem.setActivePlayerIndex(startIdx);
				}
				else if (startIdx == gSaveSystem.getNumPlayers() && gSaveSystem.getNumPlayers() < MAX_SAVED_PLAYERS) {
					selectedLevelToStart = 0;
					isNamingPlayer = true;
					namingTargetSlot = -1;
					nameInputBuffer[0] = '\0';
					nameInputLen = 0;
				}
				return;
			}

			// Slot 2
			if (mx >= BTN_OPT_P2_X1 && mx <= BTN_OPT_P2_X2 &&
				my >= BTN_OPT_P2_Y1 && my <= BTN_OPT_P2_Y2) {
				if (startIdx + 1 < gSaveSystem.getNumPlayers()) {
					gSaveSystem.setActivePlayerIndex(startIdx + 1);
				}
				else if (startIdx + 1 == gSaveSystem.getNumPlayers() && gSaveSystem.getNumPlayers() < MAX_SAVED_PLAYERS) {
					selectedLevelToStart = 0;
					isNamingPlayer = true;
					namingTargetSlot = -1;
					nameInputBuffer[0] = '\0';
					nameInputLen = 0;
				}
				return;
			}

			// Slot 3
			if (mx >= BTN_OPT_P3_X1 && mx <= BTN_OPT_P3_X2 &&
				my >= BTN_OPT_P3_Y1 && my <= BTN_OPT_P3_Y2) {
				if (startIdx + 2 < gSaveSystem.getNumPlayers()) {
					gSaveSystem.setActivePlayerIndex(startIdx + 2);
				}
				else if (startIdx + 2 == gSaveSystem.getNumPlayers() && gSaveSystem.getNumPlayers() < MAX_SAVED_PLAYERS) {
					selectedLevelToStart = 0;
					isNamingPlayer = true;
					namingTargetSlot = -1;
					nameInputBuffer[0] = '\0';
					nameInputLen = 0;
				}
				return;
			}

			// Back to Menu
			if (mx >= BTN_OPT_BACK_X1 && mx <= BTN_OPT_BACK_X2 &&
				my >= BTN_OPT_BACK_Y1 && my <= BTN_OPT_BACK_Y2) {
				currentScreen = SCREEN_MENU;
				return;
			}
			return;
		}