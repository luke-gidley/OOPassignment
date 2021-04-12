#include "Ball.h"


Ball::Ball(double x, double y, int radius, int angle, int speed) : x(x), y(y), radius(radius), angle(angle), speed(speed)
{
	direction.dx = 0;
	direction.dy = 0;
}

Ball::~Ball()
{

}
//starts the movement and calculates the angle of a bounce.
DIRECTION Ball::startMovement(double ballAngle)
{
	DIRECTION direction;

	direction.dx = cos(calcRadians(ballAngle));
	direction.dy = sin(calcRadians(ballAngle));

	return direction;

}

//collision checks
void Ball::collision(vector<Block*>* blocks, Paddle* paddle)
{
	//left and right wall
	if (x <= 0 + radius || x >= 800 - radius * 2)
	{
		direction.dx = -direction.dx;
	}
	//top
	if (y - radius <= 0)
		direction.dy = -direction.dy;
	//blocks
	for (int i = 0; i < blocks->size(); i++)
	{	
		if ((
			(x + radius > blocks->at(i)->getBotLC().x && x - radius < blocks->at(i)->getBotRC().x)) &&
			y < blocks->at(i)->getBotLC().y && y > blocks->at(i)->getTopLC().y) {
			//ignores changing direction if the juggernaut is active.
			if(!SharedData::getSharedData()->getJuggernautActive())
				direction.dx = -direction.dx;

			destroyBlock(blocks, i);
		}
		else if((
			((y + radius > blocks->at(i)->getTopLC().y) && (y - radius < blocks->at(i)->getBotLC().y))) &&
			x > blocks->at(i)->getBotLC().x && x < blocks->at(i)->getBotRC().x)
		{
			if (!SharedData::getSharedData()->getJuggernautActive())
				direction.dy = -direction.dy;

			destroyBlock(blocks, i);
		}
		


		
	}
	//paddle
	if (y >= paddle->getY() - radius && y <= paddle->getY() + paddle->getHeight() && (x > paddle->getX() && x < paddle->getX() + paddle->getWidth()))
	{
		int diff = 0;
		if(x > paddle->getX() + paddle->getWidth() / 2)
			diff = x - paddle->getX() + paddle->getWidth() / 2;

		if (x < paddle->getX() + paddle->getWidth() / 2)
			diff = paddle->getX() + paddle->getWidth() / 2 - x;
	
		if (SharedData::getSharedData()->getBigPaddleActive())
			diff /= 3;

		//not 100% sure if the bouncing angles work exactly like they should, but this adds some fun randomness that the game needed.

		if (direction.dx > 0)
		{
			direction = startMovement(90 + diff);
			direction.dx = -direction.dx;
		}
		else {
			direction = startMovement(90 + diff);
		}
	}
	//if the ball goes below the paddle the game ends.
	if (y > paddle->getY() + paddle->getHeight())
	{
		SharedData::getSharedData()->changeGameOver();
		
	}

}

//deletes a block from the vector holding it and deletes itself.
void Ball::destroyBlock(vector<Block*>* blocks, int i)
{
	bool broken = blocks->at(i)->takeDamage();
	if (broken)
	{
		SharedData::getSharedData()->changeScore(blocks->at(i)->getScoreWorth());
		delete blocks->at(i);
		blocks->erase(blocks->begin() + i);
	}
}

void Ball::drawBall(EasyGraphics* window)
{
	window->setBackColour(window->GREY);
	window->setPenColour(window->BLACK, 1);
	window->drawCircle(x, y, radius, true);
}