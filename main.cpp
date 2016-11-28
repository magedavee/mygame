#include "Game.h"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;
int main(int argc,char* args[])
{
	XInitThreads();	
	//cerr<<"db. main 000\n";
	Game* game=Game::getInstance();
	//cerr<<"db. main 001\n";
	if(game)
	{
	    game->setCMDLine(argc,args);
	    //cerr<<"db. main 002\n";
	    game->mainGameLoop();
	    //cerr<<"db. main 003\n";
	    delete game;
	    return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
