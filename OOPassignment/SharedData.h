#pragma once
#include <vector>
#include "PowerUp.h"

using namespace std;

class SharedData
{
public:

	static SharedData* getSharedData();
	static void deleteSharedData();
	void addPowerUp(PowerUp* powerUp);
	vector<PowerUp*>* getPowerUps();

	bool getBigPaddleActive();
	void changeBigPaddleActive();
	int getBigPaddleTimer();
	void changeBigPaddleTimer(int change);

	void changeGameOver();
	bool getGameOver();

	bool getJuggernautActive();
	void changeJuggernautActive();
	int getJuggernautTimer();
	void changeJuggernautTimer(int change);

	bool getDoubleSpeedActive();
	void changeDoubleSpeedActive();
	int getDoubleSpeedTimer();
	void changeDoubleSpeedTimer(int change);

	int getScore();
	void changeScore(int change);
	
	int getScoreboardSortType();
	void changeScoreboardType(int change);

	bool getGameEnded();
	void setGameEnded(bool value);
private:

	vector<PowerUp*>* activePowerUps;
	SharedData();
	static SharedData* sharedData;
	~SharedData();
	bool bigPaddleActive;
	int bigPaddleTimer;
	bool gameOver;
	bool juggernautActive;
	int juggernautTimer;

	bool doubleSpeedActive;
	int doubleSpeedTimer;

	int currentScore;
	int scoreboardType;

	bool gameEnded;
};

inline SharedData* SharedData::getSharedData()
{
	if (sharedData == nullptr)
		sharedData = new SharedData();
	return sharedData;
}


inline void SharedData::deleteSharedData()
{
	if (sharedData != NULL)
	{
		delete sharedData;
		sharedData = NULL;
	}
}


inline void SharedData::addPowerUp(PowerUp* powerUp)
{
	activePowerUps->push_back(powerUp);
}

inline vector<PowerUp*>* SharedData::getPowerUps()
{
	return activePowerUps;
}

inline bool SharedData::getBigPaddleActive() { return bigPaddleActive; }

inline void SharedData::changeBigPaddleActive() { bigPaddleActive = !bigPaddleActive; }

inline int SharedData::getBigPaddleTimer() { return bigPaddleTimer; }

inline void SharedData::changeBigPaddleTimer(int change) { bigPaddleTimer += change; }

inline void SharedData::changeGameOver() { gameOver = !gameOver; }

inline bool SharedData::getGameOver() { return gameOver; }

inline bool SharedData::getJuggernautActive() { return juggernautActive;  }

inline void SharedData::changeJuggernautActive() { juggernautActive = !juggernautActive; }

inline int SharedData::getJuggernautTimer() { return juggernautTimer; }

inline void SharedData::changeJuggernautTimer(int change) { juggernautTimer += change; }

inline bool SharedData::getDoubleSpeedActive() { return doubleSpeedActive; }

inline void SharedData::changeDoubleSpeedActive() { doubleSpeedActive = !doubleSpeedActive; }

inline int SharedData::getDoubleSpeedTimer() { return doubleSpeedTimer; }

inline void SharedData::changeDoubleSpeedTimer(int change) { doubleSpeedTimer += change; }

inline int SharedData::getScore() { return currentScore;  }

inline void SharedData::changeScore(int change) { currentScore += change; }

inline int SharedData::getScoreboardSortType() { return scoreboardType; }

inline void SharedData::changeScoreboardType(int change) { scoreboardType = change; }

inline bool SharedData::getGameEnded() { return gameEnded; }

inline void SharedData::setGameEnded(bool value) { gameEnded = value; }