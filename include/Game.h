


#ifndef GAME_H_
#define GAME_H_
#include "Graphics.h"
#include "SDLINC.h"
#include "Texture.h"
class Graphics;
class Texture;



class Game
{
protected:
	Game();
private:
	SDL_Event event;
	Graphics *graphics;
	Texture* text;
	int argc;
	char *args[];
	void processCMDLine();
//	Game(int argc, char* args[]);
//	static Game *  instance;

public:
	char * assetDir;
	static Game * getInstance();
	static bool DEBUG_ALL,DEBUG_FPS,DEBUG,DEBUG_GRAPHICS;
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
