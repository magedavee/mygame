#ifndef SPROBJ_H
#define SPROBJ_H
#include "Sprited.h"
#include "SpriteSheet.h"
#include "Object.h"
#include "Graphics.h"
#include "Game.h"
#include <string>
class SpriteSheet;
class Game;
class SpritedObject: public Object,public Sprited 
{

    public:
	SpritedObject();
	SpritedObject(string name);
	void update();
	void render();
};

#endif
