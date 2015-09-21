#ifndef GAME_H_
#define GAME_H_
#include "Graphics.h"
#include "SDLINC.h"
#include "Texture.h"
#include "SpriteSheet.h"
class Graphics;
class Texture;
class SpriteSheet;


class Game
{
protected:
	Game();
private:
	int initGame();
	SDL_Event event;
	Graphics *graphics;
	Texture* text;
	SpriteSheet * sprite;
	int argc;
	char *args[];
	void processCMDLine();
//	Game(int argc, char* args[]);
//	static Game *  instance;

public:
	enum GraphicsMode
	{
	    OGL,
	    SDL
	} graphMode;
	char * assetDir;
	static Game * getInstance();
	static bool DEBUG_ALL,DEBUG_FPS,DEBUG;
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
