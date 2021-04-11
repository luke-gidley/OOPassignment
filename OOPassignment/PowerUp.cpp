#include "PowerUp.h"
#include "SharedData.h"
#include "BigPaddle.h"
#include "Juggernaut.h"
#include "DoubleSpeed.h"

PowerUp::PowerUp()
{

}

PowerUp::PowerUp(int x, int y) : x(x), y(y)
{

}

PowerUp::~PowerUp()
{

}
//collision with paddle
bool PowerUp::collision(Paddle* paddle)
{
		if (this != nullptr) {
			if (getY() >= paddle->getY() && getY() <= paddle->getY() + paddle->getHeight() && (getX() > paddle->getX() && getX() < paddle->getX() + paddle->getWidth()))
			{
				//depending on which type of powerup was falling one is executed. It doesn't know which one it is until this point as they are randomly generated at runtime.
				if (BigPaddle* bigPaddle = dynamic_cast<BigPaddle*>(this))
				{
					bigPaddle->useBigPaddle(paddle);
				}
				else if (Juggernaut* juggernaut = dynamic_cast<Juggernaut*>(this))
				{
					juggernaut->useJuggernaut();
				}
				else if (DoubleSpeed* doubleSpeed = dynamic_cast<DoubleSpeed*>(this))
				{
		 			doubleSpeed->useDoubleSpeed();
				}


				deletePowerUp();
			}
			else if (getY() > 600)
			{
				deletePowerUp();
			}

		}
	return true;
}           

//finds and deletes the powerUp that was just hit by the paddle or fell off the screen.
void PowerUp::deletePowerUp()
{
	vector<PowerUp*>::iterator itr = find(SharedData::getSharedData()->getPowerUps()->begin(), SharedData::getSharedData()->getPowerUps()->end(), this);
	if (itr != SharedData::getSharedData()->getPowerUps()->cend())
	{
		auto location = distance(SharedData::getSharedData()->getPowerUps()->begin(), itr);
		SharedData::getSharedData()->getPowerUps()->erase(SharedData::getSharedData()->getPowerUps()->begin() + distance(SharedData::getSharedData()->getPowerUps()->begin(), itr));
		delete this;
	}
}