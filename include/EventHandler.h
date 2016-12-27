#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H


#include<map> 
#include<vector> 
#include<string> 
#include<memory> 
using namespace std;
//class Event
//{
    //map<string,bool> flag
//};
class EventHandler
{
    protected:
	map<string,bool> flags;
	map<string,int> i_states;
	map<string,float> f_states;
	map<string,char> c_states;
	vector<string> events;
    public:
    //EventHandler():flags{{"QUIT",false}},events{"OUIT"}
    //{
    //};
    void virtual pollingEvent()=0;
    bool virtual initEventHandler()=0;
    bool virtual checkFlag(string flag)
    {
	return flags[flag];
    };
    

};

class VEventHandlerRegistrar 
{
    public:
	virtual shared_ptr<EventHandler> getEventHandler()=0;
};

class EventHandlerFactory 
{
    private:
	std::map<std::string, VEventHandlerRegistrar*> registry_;
	EventHandlerFactory(): registry_() {};
	EventHandlerFactory(EventHandlerFactory const&) =delete;
	void operator=(EventHandlerFactory const&)=delete ;
    public:
	static EventHandlerFactory& getInstance();
	void registerClass(VEventHandlerRegistrar * registrar,std::string name);
	std::shared_ptr<EventHandler> getEventHandler(std::string name);
};
template<class TEventHandler>
class EventHandlerRegistrar:VEventHandlerRegistrar
{
    std::shared_ptr<EventHandler> plugin;
    public:
	EventHandlerRegistrar(std::string classname): classname_(classname),plugin(new TEventHandler())

	    {
		EventHandlerFactory &factory = EventHandlerFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::shared_ptr<EventHandler> getEventHandler()
	{
	    	    return plugin;
	};
    private:
	std::string classname_;
};

#define REGISTER_EVENT_HANDLER(CLASSNAME) \
	namespace { \
	    static EventHandlerRegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };


#endif
