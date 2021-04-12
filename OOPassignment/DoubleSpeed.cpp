#include "DoubleSpeed.h"
#include "SharedData.h"

DoubleSpeed::DoubleSpeed(int x, int y, int score) : x(x), y(y), score(score)
{

}

DoubleSpeed::~DoubleSpeed()
{

}

void DoubleSpeed::drawPowerUp(EasyGraphics* window)
{
	window->setBackColour(window->GREEN);
	window->drawCircle(x, y, 5, true);
}

//when a collsion is made with the paddle the powerup is activated.
void DoubleSpeed::useDoubleSpeed()
{
	if(!SharedData::getSharedData()->getDoubleSpeedActive())
		SharedData::getSharedData()->changeDoubleSpeedActive();

	SharedData::getSharedData()->changeDoubleSpeedTimer(DOUBLE_TIME - SharedData::getSharedData()->getDoubleSpeedTimer());
}