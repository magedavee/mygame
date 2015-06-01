#include "Game.h"
#include <X11/Xlib.h>
int main(int argc,char* args[])
{
	XInitThreads();	
//	Game* game=new Game(argc,args);
//	game->mainGameLoop();
//	Game Game::instance(argc,args);
	Game* game=Game::getInstance();
//	Game::getInstance()->setCMDLine(argc,args);
	game->setCMDLine(argc,args);
//	Game::getInstance()->assetDir="/home/mage/workspace/mygame/";
//	Game::getInstance()->getGraphics()->freeTexture(NULL);
//	Game::getInstance()->mainGameLoop();
	game->mainGameLoop();
	delete game;
	return 0;
}
