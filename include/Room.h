#ifndef SCREEN_H
#define SCREEN_H
#include "Game.h"
//#include "SDLINC.h"
#include "Object.h"
#include <vector>
#include <string>
#include <map>
#include <memory>
class Object;
class Game;
class VRoom
{
    public:
	virtual void update()=0;
	virtual void render()=0;
};

class VRoomRegistrar 
{
    public:        
	virtual std::  unique_ptr<VRoom> getRoom() = 0;
};    

class RoomFactory 
{
    private:
	std::map<std::string, VRoomRegistrar*> registry_;
	RoomFactory(): registry_() {};
	RoomFactory(RoomFactory const&) =delete;
	void operator=(RoomFactory const&)=delete ;
    public:
	static RoomFactory& getInstance()
	{
	    static RoomFactory instance;
	    return instance;
	};
	void registerClass(VRoomRegistrar * registrar,std::string name)
	{
	    registry_[name] = registrar;
	};
	std::unique_ptr<VRoom> getRoom(std::string name)
	{
		    /* throws out_of_range if plugin unknown */
	    VRoomRegistrar* registrar = registry_.at(name);
	    return registrar->getRoom();
	};
};
template<class TPlugin>
class RoomRegistrar:VRoomRegistrar
{
    public:
	RoomRegistrar(std::string classname): classname_(classname)
	    {
		RoomFactory &factory = RoomFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::unique_ptr<VRoom> getRoom()
	{
	    std::unique_ptr<VRoom> room(new TPlugin());
	    return room;
	};
    private:
	std::string classname_;
};

class Room:public VRoom
{
    protected:
	vector<Object*>  s_obj;
	Game *game;
    public:
	Room();
	void update();
	void render();

};




#define REGISTER_ROOM(CLASSNAME) \
	namespace { \
	    static RoomRegistrar<CLASSNAME> _registrar( #CLASSNAME ); \
    };
#endif
