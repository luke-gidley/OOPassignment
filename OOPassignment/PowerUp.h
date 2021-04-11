#pragma once
#include <string>
#include "Paddle.h"



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
	void deletePowerUp();

protected:
	

private:
	int x, y;


};



