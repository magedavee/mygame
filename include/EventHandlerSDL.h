#ifndef EVENT_SDL
#define EVENT_SDL
#include"EventHandler.h"
#include"Event.h"
#include "SDLINC.h"
#include<map> 
#include<vector> 
#include<string> 
#include<memory> 
using namespace std;

class EventHandlerSDL:public EventHandler
{
    vector<shared_ptr<Event>> event_list;
    SDL_Event event;
    public:
	EventHandlerSDL();
	void pollingEvent();
	bool initEventHandler();
};

#endif
