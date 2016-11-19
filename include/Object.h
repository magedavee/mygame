#ifndef OBJ_H
#define OBJ_H

#include "SpriteSheet.h"
#include "Game.h"
#include <string>
class SpriteSheet;
class Game;

class Object
{
    protected:
	Game * game;

    public:
	Object(){};
	virtual void update(){};
	virtual void render(){};
};

#endif
