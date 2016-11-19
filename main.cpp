#include "Game.h"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;
int main(int argc,char* args[])
{
	XInitThreads();	
	Game* game=Game::getInstance();
	game->setCMDLine(argc,args);
	game->mainGameLoop();
	delete game;
	return 0;
}
