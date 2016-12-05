#include"Magus.h"
#include"SpriteSheet.h"
#include"Graphics.h"
#include<string>
#include<vector>
REGISTER_OBJECT(Magus)
void Magus::init(Object* obj,string id)
{
    string name = "/home/mage/Pictures/GameSprites/res/magus2.png";
    obj->setX(0);
    obj->setY(0);
    obj->addSprite(name);
    for(int i=0;i<5;++i)
    {
	Rects* rect=new Rects();
	rect->x=32*i;
	rect->y=0;
	rect->h=32;
	rect->w=32;
	obj->getSprites()->at(0)->addRect(rect);
    }
    
    //obj->setSprites(new vector<SpriteSheet*>());
}
void Magus::render(Object* obj)
{
    //cerr<<"db magus render \n";
    auto game=Game::getInstance();
    Rects* dst=new Rects();
    dst->x=obj->getX();
    dst->y=obj->getY();
    dst->w=32;
    dst->h=32;
    //cerr<<"db dst "<<dst<<endl;
    Rects* src=obj->getSprites()->at(0)->getFrameRect();
    //cerr<<"db src "<<src<<endl;
    Texture* text=obj->getSprites()->at(0)->getTexture();
    Graphics * graphics=game->getGraphics();
    //cerr<<"db graphics "<<graphics<<endl;
    game->getGraphics()->render(text,src,dst);
}
void Magus::update(Object* obj)
{

}
