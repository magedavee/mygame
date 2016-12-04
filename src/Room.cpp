#include"Room.h"
#include <iostream>
using namespace std;
REGISTER_ROOM(Room)
Room::Room()
{
    //cerr<<"db. Room\n";
    game=Game::getInstance();
    s_obj= vector<Object*>();
    Object* obj=new Object("Magus");
    s_obj.push_back(obj);
}

void Room::update()
{
    for(auto so: s_obj)
    {
	so->update();
    }
}
void Room::render()
{
    for(auto so: s_obj)
    {
	so->render();
    }
}
