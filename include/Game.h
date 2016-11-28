#ifndef GAME_H_
#define GAME_H_
#include "Graphics.h"
#include "SDLINC.h"
#include "Monitor.h"
#include <vector>
#include <string>
#include <map>
#include <libconfig.h++>
class Graphics;
class Texture;
class SpriteSheet;
class Object;
class SpritedObject;
class Monitor;

using namespace libconfig;
typedef struct
{
    string g_mode;
}
GameSettings;
class Game
{
protected:
	Game();
private:
	bool initGame();
	SDL_Event event;
	Graphics *graphics;
	Monitor * monitor ;
	int argc;
	char *args[];
	void processCMDLine();
	GameSettings game_settings;
	map<string,int> modes;

public:
	enum GraphicsMode
	{
	    OGL,
	    SDL
	} graphMode;
	char * assetDir;
	static Game * getInstance();
	virtual ~Game();
	void setCMDLine(int arcg,char *args[]);
	void mainGameLoop();
	
	/*
		The Top level of the game loop. Polls Events, updates state, renders to sceen.
	*/
	void update();
	/*
		after all the event flags are set, updates state of game.
	*/
	void render();
	/*
		renders to the sceen.
	*/
	Graphics * getGraphics();

};



#endif
