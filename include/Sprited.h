#ifndef SPR_H
#define SPR_H
#include "Sprited.h"
#include "SpriteSheet.h"
#include "Object.h"
#include "Graphics.h"
#include "Game.h"
#include <string>
#include<vector>
class Sprited
{
    protected:
	vector <SpriteSheet *> sprite;
	vector <Rects *> src;
	vector <Rects *> dst;
	int frame,delay,delay_start;
    public:
	Sprited(){};
	virtual void render()=0;
};
#endif
