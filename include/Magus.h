#ifndef MAGUS
#define MAGUS
#include"Object.h"
#include"SpriteSheet.h"
#include"Graphics.h"
#include<vector>
class Magus:public Object
{
    SpriteSheet *sprite;
    vector<Rects*> rects;  
    int x,y,frame,counter,pause;
    public:
	Magus();
	void update();
	void render();
};
#endif
