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


void SharedData::deletePowerUp(PowerUp* powerup)
{
	//creates an iterator, finds the location of the powerup to be deleted.
	vector<PowerUp*>::iterator itr = find(activePowerUps->begin(), activePowerUps->end(), powerup);
	if (itr != activePowerUps->cend())
	{
		//finds how far from the start the powerup is.
		auto location = distance(activePowerUps->begin(), itr);
		//deletes the pointer from the vector.
		SharedData::activePowerUps->erase(activePowerUps->begin() + distance(activePowerUps->begin(), itr));
		//deletes the powerup itself.
		delete powerup;
	}
}