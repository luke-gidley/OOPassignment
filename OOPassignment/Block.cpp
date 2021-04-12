#include "Block.h"


const int NUM_OF_POWERUPS = 3;

Block::Block(int x, int y, int width, int height, int colour, int health, bool containsPowerup): x(x), y(y), width(width), height(height), colour(colour), health(health), containsPowerup(containsPowerup)
{
	//implementing corners so that when I do collision detection the if statements are actually readable.
	topLC.x = x;
	topLC.y = y;

	botLC.x = x;
	botLC.y = y + height;

	topRC.x = x + width;
	topRC.y = y;

	botRC.x = x + width;
	botRC.y = y + height;

	//sets the powerup to be a null pointer until it is created.
	powerUp = nullptr;


}

Block::~Block()
{
	
}

//When a block is hit it creates a powerup if it contains one.
bool Block::takeDamage()
{
		if (containsPowerup)
		{
			int randomPowerUp = rand() % NUM_OF_POWERUPS + 1;

			switch (randomPowerUp)
			{
			case 1:
				powerUp = new BigPaddle(x + width / 2, y + height / 2, 3);
				break;
			case 2:
				powerUp = new Juggernaut(x + width / 2, y + height / 2, 5);
				break;
			case 3: 
				powerUp = new DoubleSpeed(x + width / 2, y + height / 2, 7);
				break;
			default:
				break;
			}

			SharedData::getSharedData()->addPowerUp(powerUp);
		}
		return true;

	return false;


}

void Block::drawBlock(EasyGraphics* window)
{
	window->setBackColour(colour);
	window->setPenColour(window->BLACK, 1);
	window->drawRectangle(x, y, width, height, true);

}