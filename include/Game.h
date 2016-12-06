#ifndef GAME_H_
#define GAME_H_
#include "SDLINC.h"
#include "Graphics.h"
#include "Room.h"
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <libconfig.h++>
class Graphics;
class Texture;
class SpriteSheet;
class Object;
class SpritedObject;
class VRoom;

using namespace libconfig;
class Game
{
protected:
	Game();
private:
	bool initGame();
	SDL_Event event;
	unique_ptr<VRoom>  room ;
	shared_ptr<Graphics>  graphics ;
	int argc;
	char *args[];
	void processCMDLine();
	map<string,int> modes;
	string graphics_mode;

public:
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
	shared_ptr<Graphics> getGraphics();

};



#endif
