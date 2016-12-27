#include <string>

#include <iostream>
#include <string>
#include "Game.h"
#include "Attributes.h"
#include "Timer.h"



static Game *  instance=NULL;
Config Game::cfg;
Game::Game()
{
	//cerr<<"db Creating game \n";
}

void Game::setCMDLine(int argc, char* args[])
{
	argc=argc;
	args=args;
	if(argc>1)
	{
		processCMDLine();
	}
}

void Game::processCMDLine()
{

	//cerr<<"db cmd line\n";

}


Game* Game::getInstance()
{
	//cerr<<"db "<<"game getInstance \n";
	bool result=true;
	if(instance == NULL)
	{
		
		//cerr<<"db "<<"game instance=NULL \n";
		instance= new Game();
		//cerr<<"db "<<"game instance= "<<instance<<" \n";
		result=instance->initGame();
		//cerr<<"db "<<result<<std::endl;
	}
	if(result)
	{
	    return instance;
	}
	else
	{
	    return NULL;
	}
}

Game::~Game()
{
    //cerr<<"db deleting game \n";

}
bool Game::initSettings()
{
    try
    {
	//cfg.readFile(file.c_str());
	cfg.readFile( setting_file);
    }
    catch(const FileIOException &fioex)
    {
	std::cerr << "I/O error while reading file "<<setting_file<< std::endl;
	return(false);
    }
    catch(const ParseException &pex)
    {
	std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
		  << " - " << pex.getError() << std::endl;
	return(false);
    }
    return true;
}
Setting& Game::lookUpRoot(string path)
{
    //cerr<<"db Game::lookUpRoot path "<<path<<endl;
    //cerr<<"db cfg "<<&cfg<<endl;
    return cfg.lookup(path);

}
bool Game::lookUpValue(string path,string name,string& value)
{
    //cerr<<"db Game::lookUpValue\n";
    Setting& settings=lookUpRoot(path);
    try
    {
	//cerr<<"db. path "<<path<<endl;
	//cerr<<"db. path "<<name<<endl;

	settings.lookupValue(name,value);
	//cerr<<"db. value "<<value<<endl;

    }
    catch(const SettingNotFoundException &nfex)
    {
	cerr<<"no setting "<<path<<endl;
	//cerr<<"db. return false \n";
	return false;
    }

    //cerr<<"db. return  true \n";
    return true;
}
bool Game::lookUpValue(Setting& settings ,string name,string& value)
{
    //cerr<<"db Game::lookUpValue Setting string string\n";
    try
    {
	//cerr<<"db. path "<<name<<endl;

	settings.lookupValue(name,value);
	//cerr<<"db. value "<<value<<endl;

    }
    catch(const SettingNotFoundException &nfex)
    {
	//cerr<<"db. return false \n";
	return false;
    }

    //cerr<<"db. return  true \n";
    return true;
}
bool Game:: initGame()
{
    //cerr<<"db "<<" init "<<std::endl;
    // Read the file. If there is an error, report it and exit.
    //string file="./settings/setting.cfg";
    if(!initSettings())
    {
	return false;
    }
    string graphics_mode;
    string event_mode;
    if(!lookUpValue("game","graphics",graphics_mode))
    {
	return false;
    }
    //cerr<<"db. initGame g_mode "<<graphics_mode<<endl;
    if(!lookUpValue("game.event","handler",event_mode))
    {
	return false;
    }
    //cerr<<"db. initGame e_mode "<<event_mode<<endl;
    
    mode["graphics"]=graphics_mode;
    mode["event_handler"]=event_mode;
    auto &g_factory = GraphicsFactory::getInstance();
    auto g=g_factory.getPlugin(graphics_mode);
    graphics=g;
    graphics->init();
    auto &e_factory = EventHandlerFactory::getInstance();
    auto e=e_factory.getEventHandler(event_mode);
    event_handler=e;
    //cerr<<"db Game  initGame before initEventHandler  \n";
    event_handler->initEventHandler();
    //cerr<<"db Game  initGame after initEventHandler  \n";
    auto &factory = RoomFactory::getInstance();
    room=factory.getRoom("Room");
    return true;
}
void Game::mainGameLoop()
{
	bool quit=false;
	Timer fps;
	while(!event_handler->checkFlag("QUIT"))
	{
	    fps.start();
	    //cerr<<"db begin main game loop\n";
	    event_handler->pollingEvent();
		
	    //cerr<<"db update\n";
	    update();
	    //cerr<<"db render\n";
	    render();	
	    if( fps.get_ticks() < 1000 / FPS ) 
	    {
		     SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() ); 
	    }
	    //cerr<<"db runing at "<<1000/fps.get_ticks()<<endl;
	
	}
}

void Game::update()
{
    room->update();
}


void Game::render()
{ 
    room->render();
}

shared_ptr<Graphics>Game::getGraphics()
{
    //cerr<<"db.Game  getGraphics\n";
    return graphics;
}
shared_ptr<EventHandler>Game::getEventHandler()
{
    //cerr<<"db.Game  getGraphics\n";
    return event_handler;
}
