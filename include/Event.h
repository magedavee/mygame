#ifndef EVENT_HH
#define EVENT_HH
#include "SDLINC.h"
#include<map> 
#include<vector> 
#include<string> 
#include<memory> 
using namespace std;
class Event
{
    protected:
    public:
    Event(){};
    virtual void initEvent(vector<string>&,map<string,bool>&,map<string,int>& ,map<string,float>&,map<string,char>&)=0;
    virtual void handleEvent(SDL_Event& event,map<string,bool>&,map<string,int>& ,map<string,float>&,map<string,char>&)=0;
    

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
