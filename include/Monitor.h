#ifndef SCREEN_H
#define SCREEN_H
#include "Game.h"
#include "SDLINC.h"
#include "Object.h"
#include "SpritedObject.h"
#include <vector>
class SpritedObject;
class Monitor
{
    protected:
	vector<SpritedObject*>  s_obj;
	SpriteSheet * sprite;
	Game *game;
    public:
	Monitor();
	void update();
	void render();

};




#endif
