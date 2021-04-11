#pragma once
#include "PowerUp.h"
#include "SharedData.h"

class BigPaddle : public PowerUp
{
public:

	BigPaddle(int x, int y, int score);
	~BigPaddle();
	void useBigPaddle(Paddle* paddle);
	virtual void drawPowerUp(EasyGraphics* window);
	virtual void movePowerUp();
	int& getY();
	int& getX();

private:

	int x, y;
	int score;

};
inline void BigPaddle::movePowerUp() {
	y += 3;
}

inline int& BigPaddle::getY() { return y; }

inline int& BigPaddle::getX() { return x; }
