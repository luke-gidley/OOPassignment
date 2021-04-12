#pragma once
#include <string>
#include "EasyGraphics.h"
#include "PowerUp.h"
#include "BigPaddle.h"
#include "SharedData.h"
#include "Juggernaut.h"
#include "DoubleSpeed.h"

using namespace std;

//more readable.
struct CORNER
{
	int x, y;
};


class Block
{
public:
	Block(int x, int y, int width, int height, int colour, int health, bool containsPowerup);
	~Block();
	void drawBlock(EasyGraphics* window);
	bool takeDamage();
	int getX();
	int getY();
	CORNER getTopLC();
	CORNER getBotLC();
	CORNER getTopRC();
	CORNER getBotRC();
	int getScoreWorth();

private:
	int health;
	int colour;
	bool containsPowerup;
	int x, y, width, height;
	const int colours[5] = { EasyGraphics::DARK_RED, EasyGraphics::RED, EasyGraphics::YELLOW, EasyGraphics::GREEN, EasyGraphics::BLUE };
	static const int scoreWorth = 1;
	CORNER topLC, botLC, topRC, botRC;
	PowerUp* powerUp;


};


inline int Block::getX()
{
	return x;
}

inline int Block::getY()
{
	return y;
}

inline CORNER Block::getTopLC()
{
	return topLC;
}

inline CORNER Block::getBotLC()
{
	return botLC;
}

inline CORNER Block::getTopRC()
{
	return topRC;
}

inline CORNER Block::getBotRC()
{
	return botRC;
}

inline int Block::getScoreWorth() { return scoreWorth; }