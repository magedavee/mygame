#include "EventQuit.h"
#include<iostream>
REGISTER_EVENT(EventQuit)
using namespace std;
EventQuit::EventQuit()
{
}

void EventQuit::handleEvent(map<string,bool>&flags,map<string,int>&i_states ,map<string,float>&f_states,map<string,char>&c_states)
{
    
    //cerr<<"db EventQuit handleEvent begin \n";
    //cerr<<"db e adderes "<<&e<<endl;
    //cerr<<"db e type  "<<e->type<<endl;
    //cerr<<"db SDL_QUIT "<<SDL_QUIT<<endl;
    if(e->type==SDL_QUIT)//exit flag
    {
	    //cerr<<"db exiting\n";
	    flags["QUIT"]=true;		
    }
    //cerr<<"db EventQuit handleEvent exiting\n";

};
void EventQuit::initEvent(SDL_Event* e_,vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states)
{
    //cerr<<"db EventQuit initEvent  Begin\n";
    e=e_;
    //cerr<<"db. e "<<e<<endl;
    //cerr<<"db. e_ "<<e_<<endl;
    //cerr<<"db  push back QUIT\n";
    events.push_back("QUIT");
    //cerr<<"db   flags[ QUIT] false\n";
    flags["QUIT"]=false;
    //cerr<<"db EventQuit initEvent  End\n";

};
