#include <Windows.h>
#include <crtdbg.h>
#include "Level.h"
#include "Block.h"
#include <time.h>
#include "SharedData.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int show)
{
#ifdef _DEBUG
	_onexit(_CrtDumpMemoryLeaks);
#endif // _DEBUG

	srand(time(NULL));
	bool gameEnded;
	do
	{
	Level *window = new Level();
	window->create(hInstance, 800, 600, 100, true);
	window->onDraw();
	delete window;
	gameEnded = SharedData::getSharedData()->getGameEnded();
	SharedData::deleteSharedData();
	} while (!gameEnded);
	
	return 0;
}