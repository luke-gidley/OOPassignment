#pragma once
#include "PowerUp.h"
class DoubleSpeed : public PowerUp
{

public:

	DoubleSpeed(int x, int y, int score);
	~DoubleSpeed();
	void useDoubleSpeed();
	virtual void drawPowerUp(EasyGraphics* window);
	virtual void movePowerUp();
	int& getY();
	int& getX();

private:

	int x, y, score;


};

inline int& DoubleSpeed::getY() { return y; }

inline int& DoubleSpeed::getX() { return x; }

inline void DoubleSpeed::movePowerUp()
{
	y += 7;
}