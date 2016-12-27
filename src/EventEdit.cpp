#include "EventEdit.h"
REGISTER_EVENT(EventEdit)

EventEdit::EventEdit():Event()
{
}

void EventEdit::handleEvent(map<string,bool>&flags,map<string,int>&i_states ,map<string,float>&f_states,map<string,char>&c_states)
{
    
    if( e->type == SDL_KEYDOWN )
    {
    }

};
void EventEdit::initEvent(SDL_Event* e_,vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states)
{
    e=e_;
    events.push_back("EDIT");
    flags["EDIT"]=false;

};
