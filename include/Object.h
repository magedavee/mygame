#ifndef OBJ_H
#define OBJ_H

#include "SpriteSheet.h"
#include "Game.h"
#include "Plugin.h"
#include <string>
class SpriteSheet;
class Game;
using namespace PluginSystem;
class Object:public VPlugin
{
    protected:
	Game * game;

    public:
	Object(){};
	virtual void update(){};
	//virtual void render(){};
};

#endif
