#include"Room.h"
#include <iostream>
#include <memory>
using namespace std;
REGISTER_ROOM(Room)
Room::Room()
{
    //cerr<<"db. Room\n";
    auto& factory=ObjectFactory::getInstance();
    auto obj=factory.getPlugin("Magus");
    s_obj= vector<shared_ptr<Object>>();
    s_obj.push_back(obj);
}

void Room::update()
{
    //cerr<<"db. Room update \n";
    for(auto so: s_obj)
    {
	so->update();
    }
}
void Room::render()
{
    //cerr<<"db. Room render \n";
    for(auto so: s_obj)
    {
	so->render();
    }
}
