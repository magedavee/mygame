#ifndef EVENT_EDIT_H
#define EVENT_EDIT_H
#include"Event.h"

class EventEdit:public Event
{

    public:
    EventEdit();
    void initEvent(SDL_Event*,vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states);
    void handleEvent(map<string,bool>&,map<string,int>& ,map<string,float>&,map<string,char>&);

};

#endif
