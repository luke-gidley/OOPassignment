#pragma once
#include "PowerUp.h"


class Juggernaut : public PowerUp
{

public:
	Juggernaut(int x, int y, int score);
	~Juggernaut();
	void useJuggernaut();
	virtual void drawPowerUp(EasyGraphics* window);
	virtual void movePowerUp();
	int& getY();
	int& getX();

private:
	int x, y;
	int score;
};

inline void Juggernaut::movePowerUp()
{
	y += 5;
}

inline int& Juggernaut::getY() { return y; }

inline int& Juggernaut::getX() { return x; }

