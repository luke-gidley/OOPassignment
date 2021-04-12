#pragma once
#include "EasyGraphics.h"
#include <math.h>
#include "Block.h"
#include <vector>
#include "Paddle.h"
#include <algorithm>


struct DIRECTION
{
	double dx, dy;
};



class Ball
{
public:

	Ball(double x, double y, int radius, int angle, int speed);
	~Ball();
	void drawBall(EasyGraphics* window);
	DIRECTION startMovement(double angle);
	void moveBall();
	double calcRadians(double degrees);
	void collision(vector<Block*>* blocks, Paddle* paddle);
	int getBallx();
	DIRECTION& changeDirection();
	int getAngle();
	void destroyBlock(vector<Block*>* blocks, int i);



private:
	int speed, angle, radius;
	double x, y;
	DIRECTION direction;



};

//moves the ball depending on direction and if double speed is active.
inline void Ball::moveBall()
{
	if (SharedData::getSharedData()->getDoubleSpeedActive()) {
		x += (direction.dx * speed*2);
		y -= (direction.dy * speed*2);
	}
	else {
		x += (direction.dx * speed);
		y -= (direction.dy * speed);
	}
}

//calculates radians.
inline double Ball::calcRadians(double degrees)
{
	const double CONVERSION = 6.283185307179586 / 360;
	return degrees * CONVERSION;
}

inline int Ball::getBallx(){ return x; }


inline DIRECTION& Ball::changeDirection() { return direction; }

inline int Ball::getAngle() { return angle; }