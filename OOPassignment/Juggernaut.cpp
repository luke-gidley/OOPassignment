#include "Juggernaut.h"
#include "SharedData.h"


void Juggernaut::drawPowerUp(EasyGraphics* window)
{
	window->setBackColour(window->BLUE);
	window->drawCircle(x, y, 5, true);
}

Juggernaut::Juggernaut(int x, int y, int score): x(x), y(y), score(score)
{

}

Juggernaut::~Juggernaut()
{

}
//sets the timer for juggernaut
void Juggernaut::useJuggernaut()
{
	if(!SharedData::getSharedData()->getJuggernautActive())
		SharedData::getSharedData()->changeJuggernautActive();

	SharedData::getSharedData()->changeJuggernautTimer(JUGGERNAUT_TIME - SharedData::getSharedData()->getJuggernautTimer());
}