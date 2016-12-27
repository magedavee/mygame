#ifndef EVENT_HH
#define EVENT_HH
#include "SDLINC.h"
#include<map> 
#include<vector> 
#include<string> 
#include<memory> 
#include<iostream> 
#include<stdint.h>
#include"EventHandlerSDL.h"
using namespace std;
class Event
{
    protected:
	SDL_Event *e;
    public:
    Event(){};
    virtual void initEvent(SDL_Event*,vector<string>&,map<string,bool>&,map<string,int>& ,map<string,float>&,map<string,char>&)=0;
    virtual void handleEvent(map<string,bool>&,map<string,int>& ,map<string,float>&,map<string,char>&)=0;
    bool testType(uint32_t type)
    {
	return e->key.keysym.sym ==type;
    };
    bool testKeyCode(uint32_t key_code)
    {
	return e->key.keysym.sym ==key_code;
    };
    bool testScanCode(uint32_t scan_code)
    {
	return e->key.keysym.sym ==scan_code;
    };
    

};

class VEventRegistrar 
{
    public:
	virtual std::shared_ptr<Event> getEvent()=0;
};

class EventFactory 
{
    private:
	std::map<std::string, VEventRegistrar*> registry_;
	EventFactory(): registry_() {};
	EventFactory(EventFactory const&) =delete;
	void operator=(EventFactory const&)=delete ;
    public:
	static EventFactory& getInstance();
	void registerClass(VEventRegistrar * registrar,std::string name);
	std::shared_ptr<Event> getEvent(std::string name);
};
template<class TEvent>
class EventRegistrar:VEventRegistrar
{
    public:
	EventRegistrar(std::string classname): classname_(classname),plugin(new TEvent())
	{
	    EventFactory &factory = EventFactory::getInstance();
	    factory.registerClass(this, classname);
	};
	std::shared_ptr<Event> getEvent()
	{
	    
	    return plugin;
	};
    private:
	std::string classname_;
	std::string name_;
	std::shared_ptr<Event> plugin;
};
#define REGISTER_EVENT(CLASSNAME) \
	namespace { \
	    static EventRegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };


#endif
