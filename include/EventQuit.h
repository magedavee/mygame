#ifndef EVENT_QUIT_H
#define EVENT_QUIT_H
#include"Event.h"

class EventQuit:public Event
{

    public:
    EventQuit();
    void initEvent(vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states);
    void handleEvent(SDL_Event& e,map<string,bool>&,map<string,int>& ,map<string,float>&,map<string,char>&);

};

#endif
