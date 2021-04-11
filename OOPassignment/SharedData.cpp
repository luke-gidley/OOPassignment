#include "SharedData.h"

SharedData* SharedData::sharedData = nullptr;


SharedData::SharedData()
{
	activePowerUps = new vector<PowerUp*>;
	bigPaddleActive = false;
	currentScore = 0;
	gameEnded = true;
}

SharedData::~SharedData()
{
	for (int i = 0; i < activePowerUps->size(); i++)
	{
		delete activePowerUps->at(i);
	}
	delete activePowerUps;
}


