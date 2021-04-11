#include "BigPaddle.h"

BigPaddle::BigPaddle(int x, int y, int score): x(x), y(y), score(score)
{

}

BigPaddle::~BigPaddle()
{

}

void BigPaddle::useBigPaddle(Paddle* paddle)
{
	if (!SharedData::getSharedData()->getBigPaddleActive())
	{
		paddle->changeWidth(100);
		SharedData::getSharedData()->changeBigPaddleActive();
	}
	
	SharedData::getSharedData()->changeBigPaddleTimer(600 - SharedData::getSharedData()->getBigPaddleTimer());
}

void BigPaddle::drawPowerUp(EasyGraphics* window) 
{
	window->setBackColour(window->RED);
	window->drawCircle(x, y, 5, true);
}