#include "GameMode.h"

GameManager::GameManager() : currentMode(MODE_SOLO_GAME) {}

void GameManager::setGameMode(GameMode mode) {
  currentMode = mode;
  // Perform any mode-specific initialization or logic here
}

GameMode GameManager::getCurrentGameMode() const {
  return currentMode;
}

// Implement any other functions or logic here


void soloPlayer() {
  // Game logic all-v-all
}

void teamDeathmatchLogic() {
  // Game logic for Team Deathmatch
}

void captureTheFlagLogic() {
  // Game logic for Capture the Flag
}

