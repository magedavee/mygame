#include "Game.h"
#include <iostream>
#include <X11/Xlib.h>
using namespace std;
int main(int argc,char* args[])
{
	XInitThreads();	
	//cerr<<"db. main 000\n";
	//Game* game=Game::getInstance();
	//cerr<<"db. main 001\n";
	auto &rte_factory = RTEFactory::getInstance();
	auto game=rte_factory.getRTE("Game");

	if(game)
	{
	    //cerr<<"db. main 002\n";
	    game->run();
	    //cerr<<"db. main 003\n";
	    return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
