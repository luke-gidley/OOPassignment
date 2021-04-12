#pragma once
#include <string>
#include "Paddle.h"


//base abstract class to allow for other powerups to work.
class PowerUp
{
public:

	PowerUp();
	PowerUp(int x, int y);
	~PowerUp();
	bool collision(Paddle* paddle);
	virtual void drawPowerUp(EasyGraphics* window)=0;
	virtual void movePowerUp()=0;
	virtual int& getY()=0;
	virtual int& getX()=0;

protected:
	

private:
	int x, y;


};



