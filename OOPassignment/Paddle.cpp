#include "Paddle.h"

Paddle::Paddle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{

}

Paddle::~Paddle()
{

}


void Paddle::drawPaddle(EasyGraphics* window)
{
	window->setBackColour(window->GREY);
	window->setPenColour(window->BLACK, 1);
	window->drawRectangle(x, y, width, height, true);
}