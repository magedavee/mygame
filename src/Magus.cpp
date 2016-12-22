#include"Magus.h"
#include"SpriteSheet.h"
#include"Graphics.h"
#include<string>
#include<vector>
REGISTER_OBJECT(Magus)
Magus::Magus():x(0),y(0),frame(0),pause(10),counter(1)
{
    //cerr<<"db Magus() \n ";
    string name = "/home/mage/Pictures/GameSprites/res/magus2.png";
    sprite=new SpriteSheet(name);
    //cerr<<"db Magus sprite "<<sprite<<endl;
    for(int i=0;i<5;++i)
    {
	Rects* rect=new Rects();
	rect->x=32*i;
	rect->y=0;
	rect->h=32;
	rect->w=32;
	sprite->addRect(rect);
    }
    
    //obj->setSprites(new vector<SpriteSheet*>());
}
void Magus::render()
{
    //cerr<<"db magus render \n";
    auto game=Game::getInstance();
    Rects* dst=new Rects();
    dst->x=x;
    dst->y=y;
    dst->w=32;
    dst->h=32;
    //cerr<<"db dst "<<dst<<endl;
    //cerr<<"db magus sprite "<<sprite<<endl;
    Rects* src=sprite->getFrameRect();
    //cerr<<"db src "<<src<<endl;
    Texture* text=sprite->getTexture();
    //cerr<<"db getGraphics "<<src<<endl;
    auto  graphics=game->getGraphics();
    //cerr<<"db getGraphics graphics "<<graphics<<endl;
    //cerr<<"db rennder "<<src<<endl;
    graphics->render(text,src,dst);
    delete dst;
}
void Magus::update()
{
    if(counter%10!=0)
    {
	++counter;
    }
    else
    {
	counter=1;
	if(frame<sprite->getMeshSize())
	{
	    //cerr<<"db. Magus update frame "<<frame<<endl;
	    sprite->setFrame(frame++);
	}
	else
	{
	    frame=0;
	}
    }

}
