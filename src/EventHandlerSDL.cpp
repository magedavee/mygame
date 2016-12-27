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
	auto &e_factory=EventFactory::getInstance();
	auto e=e_factory.getEvent(name);
	event_list.push_back(e);
	e->initEvent(events,flags,i_states,f_states,c_states);
	//cerr<<"db event_list size "<<event_list.size()<<endl;

    }

};

void EventHandlerSDL::pollingEvent()
{
    while(SDL_PollEvent(&event))//polling
    {

	//cerr<<"db EventSDL pollingEvent event type "<<event.type<<endl;
	//cerr<<"db. <<"<<SDL_QUIT<<endl;
	for(auto e:event_list)
	{
	    if(flags["QUIT"])
	    {
		break;
	    }
	    e->handleEvent(event,flags,i_states,f_states,c_states);

	}
    }
     
}
