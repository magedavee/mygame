#include "EventQuit.h"
REGISTER_EVENT(EventQuit)

EventQuit::EventQuit()
{
}

void EventQuit::handleEvent(SDL_Event& e,map<string,bool>&flags,map<string,int>&i_states ,map<string,float>&f_states,map<string,char>&c_states)
{
    
    if(e.type==SDL_QUIT)//exit flag
    {
	    //cerr<<"db exiting\n";
	    flags["QUIT"]=true;		
    }

};
void EventQuit::initEvent(vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states)
{
    events.push_back("QUIT");
    flags["QUIT"]=false;

};
