#include"SpritedObject.h"
#include <string>
#include <iostream>
#include <vector>
#include "Game.h"

using namespace std;
SpritedObject::SpritedObject()
{
    game=Game::getInstance();
    frame=1;
    delay_start=10;
    delay=delay_start;
}

SpritedObject::SpritedObject(string name):SpritedObject()
{
    SpriteSheet* s=new SpriteSheet(name);
    sprite= vector<SpriteSheet*>();
    src= vector<Rects*>();
    dst= vector<Rects*>();
    sprite.push_back(s);
    for(int i=0;i<9;++i)
    {
	Rects* sR=new Rects();
	sR->x=148+i*32;
	sR->y=200;
	sR->h=32;
	sR->w=32;
	src.push_back(sR);
    }
    Rects* dR=new Rects();
    dR->x=108;
    dR->y=210;
    dR->h=48;
    dR->w=32;
    dst.push_back(dR);

    game=Game::getInstance();
}

void SpritedObject::update()
{
    //cerr<<"db. SpriteObject update 000 frame "<<frame<<endl;
    //cerr<<"db. SpriteObject update 000 src.size "<<src.size()<<endl;
    if(delay >0)
    {
	--delay;
	//cerr<<"db.\n delay"<<delay<<endl;
    }
    else
    {
	if(frame%src.size()!=0)
	{
	    //cerr<<"db. SpriteObject update 001 frame "<<frame<<endl;
	    ++frame;
	}
	else
	{
	    //cerr<<"db. SpriteObject update 002 frame "<<frame<<endl;
	    frame=1;
	}
	delay=delay_start;
    }
}

void SpritedObject::render()
{
    //cerr<<"db SpriteObject render 100 frame "<<frame<<endl;
    Rects* sR=src[frame-1];
    Rects* dR=dst[0];
    game->getGraphics()->render(sprite[0]->getTexture(),sR,dR);
}


