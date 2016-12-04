#include <string>

#include <iostream>
#include <string>
#include "Game.h"
#include "Attributes.h"
#include "Timer.h"



static Game *  instance=NULL;
Game::Game()
{
	//cerr<<"db Creating game \n";
    modes["OGL"]=OGL;
    modes["SDL"]=SDL;
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

bool Game:: initGame()
{
    //cerr<<"db "<<" init "<<std::endl;
    Config cfg;
    // Read the file. If there is an error, report it and exit.
    string file="./settings/setting.cfg";
    try
    {
	cfg.readFile(file.c_str());
    }
    catch(const FileIOException &fioex)
    {
	std::cerr << "I/O error while reading file "<<file<< std::endl;
	return(false);
    }
    catch(const ParseException &pex)
    {
	std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
		  << " - " << pex.getError() << std::endl;
	return(false);
    }
    
    Setting& settings=cfg.getRoot();
    string g_mode;
    settings["game"].lookupValue("graphics",g_mode);
    game_settings.g_mode=g_mode;
    graphMode=OGL;
    switch(modes[g_mode])
    {
    case SDL:
	//cerr<<"db SDL graphics mode\n";
	this->graphics=new GraphicsSDL();
	break;
    case OGL:
	//cerr<<"db OpenGL graphics mode\n";
	this->graphics=new GraphicsGL();
	break;
    }
    auto &factory = RoomFactory::getInstance();
    //room =new Room();
    room=factory.getRoom("Room");
    return true;
}
void Game::mainGameLoop()
{
	bool quit=false;
	Timer fps;
	while(!quit)
	{
		fps.start();
		//cerr<<"db begin main game loop\n";
		while(SDL_PollEvent(&event))//polling
		{

		    //cerr<<"db event type "<<event.type<<endl;
			if(event.type==SDL_QUIT)//exit flag
			{
				//cerr<<"db exiting\n";
				quit=true;		
			}
		}
		
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

Graphics* Game::getGraphics()
{
	return this->graphics;
}
