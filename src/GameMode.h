// GameManager.h

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

enum GameMode {
  MODE_SOLO_GAME,
  MODE_TEAM_DEATHMATCH,
  MODE_CAPTURE_THE_FLAG,
  // Add more game modes as needed
};

class GameManager {
public:
  GameManager();
  void setGameMode(GameMode mode);
  GameMode getCurrentGameMode() const;

private:
  GameMode currentMode;
};

// Declare any other relevant functions or classes here

#endif // GAMEMANAGER_H