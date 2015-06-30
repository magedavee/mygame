#include "Game.h"
#include <X11/Xlib.h>
int main(int argc,char* args[])
{
	XInitThreads();	
	Game* game=Game::getInstance();
	game->setCMDLine(argc,args);
	game->mainGameLoop();
	delete game;
	return 0;
}
