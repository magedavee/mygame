#include"EventHandlerSDL.h"
#include"Event.h"
#include"Game.h"
#include<iostream>
using namespace std;
REGISTER_EVENT_HANDLER(EventHandlerSDL)
EventHandlerSDL::EventHandlerSDL()
{
    //cerr<<"db EventHandlerSDL \n";

}

bool EventHandlerSDL::initEventHandler()
{
    //cerr<<"db EventHandlerSDL initEventHandler \n";
    Setting& event_settings=Game::lookUpRoot("game.event.events");
    int count = event_settings.getLength();
    for(int i=0;i<count;++i)
    {

	string name =event_settings[i];
	//cerr<<"db name "<<name<<endl;
	auto &ev_factory=EventFactory::getInstance();
	auto ev=ev_factory.getEvent(name);
	ev->initEvent(&e,events,flags,i_states,f_states,c_states);
	event_list.push_back(ev);
	//cerr<<"db event_list size "<<event_list.size()<<endl;

    }

};

void EventHandlerSDL::pollingEvent()
{
    while(SDL_PollEvent(&e))//polling
    {

	//cerr<<"db EventSDL pollingEvent Begin#####\n";
	//cerr<<"db  event addr "<<&e<<endl;
	//cerr<<"db  event type "<<e.type<<endl;
	for(auto ev:event_list)
	{
	    if(flags["QUIT"])
	    {
		//cerr<<"db EventHandlerSDL polling Event QUIT break\n";
		break;
	    }
	    //cerr<<"db  befor event addr "<<&e<<endl;
	    //cerr<<"db  befor event type "<<e.type<<endl;
	    ev->handleEvent(flags,i_states,f_states,c_states);
	    //cerr<<"db  befor event addr "<<&e<<endl;
	    //cerr<<"db  befor event type "<<e.type<<endl;

	}
    }
     
}
