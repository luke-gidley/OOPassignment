#pragma once
#include "EasyGraphics.h"
class Paddle
{
public:

	Paddle(int x, int y, int width, int height);
	~Paddle();
	void drawPaddle(EasyGraphics* window);
	void movePaddle(int x);
	int getX();
	int getY();
	int getWidth();
	void changeWidth(int change);
	int getHeight();

private:
	int x, y, width, height;
};



inline void Paddle::movePaddle(int x) 
{
	this->x = x;
}

inline int Paddle::getX()
{
	return x;
}

inline int Paddle::getY()
{
	return y;
}

inline int Paddle::getWidth()
{
	return width;
}

inline void Paddle::changeWidth(int change){ width += change; }

inline int Paddle::getHeight() { return height; }