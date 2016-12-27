#include "EventKB.h"
#include<iostream>
REGISTER_EVENT(EventKB)
using namespace std;
EventKB::EventKB()
{
}

void EventKB::handleEvent(SDL_Event& e,map<string,bool>&flags,map<string,int>&i_states ,map<string,float>&f_states,map<string,char>&c_states)
{
    if( e.type == SDL_KEYDOWN ) 
    { 
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	cout<<"key : "<<e.key.keysym.sym<<endl;
    }

};
void EventKB::initEvent(vector<string>& events,map<string,bool>& flags,map<string,int>& i_states ,map<string,float>& f_states ,map<string,char>& c_states)
{
    events.push_back("QUIT");
    flags["QUIT"]=false;

};
