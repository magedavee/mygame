#ifndef SPROBJ_H
#define SPROBJ_H

#include "SpriteSheet.h"
#include "Object.h"
#include "Graphics.h"
#include "Game.h"
#include <string>
class SpriteSheet;
class Game;
class SpritedObject:public Object
{
    protected:
	vector <SpriteSheet *> sprite;
	vector <Rects *> src;
	vector <Rects *> dst;
	Game * game;
	int frame,delay,delay_start;

    public:
	SpritedObject();
	SpritedObject(string name);
	void update();
	void render();
};

#endif
