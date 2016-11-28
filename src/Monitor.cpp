#include"Monitor.h"
#include <iostream>
using namespace std;
Monitor::Monitor()
{
    //cerr<<"db. Monitor\n";
    SpritedObject* sO=new SpritedObject("/home/mage/Pictures/GameSprites/res/magusSheet.png");
    game=Game::getInstance();
    s_obj= vector<SpritedObject*>();
    s_obj.push_back(sO);
}

void Monitor::update()
{
    for(auto so: s_obj)
    {
	so->update();
    }
}
void Monitor::render()
{
    for(auto so: s_obj)
    {
	so->render();
    }
}
