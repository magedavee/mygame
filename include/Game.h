#ifndef GAME_H_
#define GAME_H_
#include "SDLINC.h"
#include "Graphics.h"
#include "Room.h"
#include "EventHandler.h"
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
class EventHandler;

using namespace libconfig;
//template<class type> bool lookUpValue(string  ,type&)
class Game
{
protected:
	Game();
private:
	bool initGame();
	shared_ptr<EventHandler>  event_handler ;
	unique_ptr<VRoom>  room ;
	shared_ptr<Graphics>  graphics ;
	int argc;
	char *args[];
	void processCMDLine();
	map<string,string> mode;
	static Config cfg;
	static constexpr const char* setting_file = "./settings/setting.cfg";

public:
	static bool initSettings();
	static bool lookUpValue(string path,string name,string& value);
	static bool lookUpValue(Setting& settings ,string name,string& value);
	static Setting& lookUpRoot(string path);
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
	shared_ptr<EventHandler> getEventHandler();

};



#endif
