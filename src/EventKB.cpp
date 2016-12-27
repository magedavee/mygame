#include "EventKB.h"
#include<iostream>
REGISTER_EVENT(EventKB)
using namespace std;
EventKB::EventKB():Event()
{
}

void EventKB::handleEvent(map<string,bool>&flags,map<string,int>&i_states ,map<string,float>&f_states,map<string,char>&c_states)
{
    flags["UP"]=false;
    flags["DOWN"]=false;
    flags["LEFT"]=false;
    flags["RIGHT"]=false;
    if( e->type == SDL_KEYDOWN ) 
    { 
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	cerr<<"db ####################\n"; 
	cerr<<"db key : "<<e->key.keysym.sym<<endl;
	cerr<<"db scan : "<<e->key.keysym.scancode<<endl;
	cerr<<"db ####################\n"; 
	switch(e->key.keysym.sym)
	{
	    case SDLK_UP:
		flags["UP"]=true;
		break;
	    case SDLK_DOWN:
		flags["DOWN"]=true;
		break;
	    case SDLK_LEFT:
		flags["LEFT"]=true;
		break;
	    case SDLK_RIGHT:
		flags["RIGHT"]=true;
		break;
	}
    }

};
void EventKB::initEvent(SDL_Event* e_,vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states)
{
    e=e_;
    events.push_back("UP");
    events.push_back("DOWN");
    events.push_back("LEFT");
    events.push_back("RIGHT");
    flags["UP"]=false;
    flags["DOWN"]=false;
    flags["LEFT"]=false;
    flags["RIGHT"]=false;

};
