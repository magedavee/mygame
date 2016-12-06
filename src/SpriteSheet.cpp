#include "SpriteSheet.h"
#include "Game.h"
#include <string>
#include <iostream>

SpriteSheet::SpriteSheet(string name):frame(0)
{
    //cerr<<"db SpriteSheet() \n ";
    Game* game=Game::getInstance();
    this->map=game->getGraphics()->loadTexture(name.c_str());
    this->render_rect.x=0;
    this->render_rect.y=0;
    this->render_rect.h=0;
    this->render_rect.w=0;
    this->mesh=new vector<Rects*>();
}


void SpriteSheet::addRect(Rects *rect)
{
    if(mesh==NULL)
    {
	mesh=new vector<Rects*>();
	//cerr<<"db addRect new mesh "<< mesh<<endl;
    }
    //cerr<<"db addRect "<< mesh<<endl;
    //cerr<<"db addRect "<< mesh->size()<<endl;

    this->mesh->push_back(rect);
    //cerr<<"db addRect did it push? "<< mesh->size()<<endl;
}

void SpriteSheet::setFrame(int frame)
{
    if (frame>=0 && frame < mesh->size())
    {
	this->frame=frame;
    }
    std::cout<<"error frame not in bounds\n";
}
Rects* SpriteSheet::getFrameRect()
{
    //cerr<<"db getFrameRect "<< mesh<<endl;
    //cerr<<"db getFrameRect "<< mesh->size()<<endl;
    return this->mesh->at(frame);
}

SpriteSheet::~SpriteSheet()
{
    for(auto it=mesh->begin();it != mesh->end();++it)
    {
	delete *it;
    }
    delete map;
    delete mesh;
}
