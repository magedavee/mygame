#include <string>

#include <iostream>
#include <string>
#include "Game.h"
#include "Attributes.h"
#include "Timer.h"


//#define DEBUG false//||DEBUG_ALL //set to true to turn on debug for this class only
//#define DEBUG_FPS false||DEBUG //set to true to see fram per sec output

static Game *  instance=NULL;
bool Game::DEBUG_ALL=false;
bool Game::DEBUG=false||Game::DEBUG_ALL;
bool Game::DEBUG_FPS=false||Game::DEBUG_ALL;
Game::Game()
{
	argc=0;
	
	this->graphMode=OGL;	
	if(DEBUG)
		std::cout<<"Creating game \n";
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

	std::cout<<"cmd line\n";

}


Game* Game::getInstance()
{
	if(instance == NULL)
	{
		
		instance= new Game();
		int result=instance->initGame();
		if(DEBUG)
			std::cout<<"game \n";
			std::cout<<result<<std::endl;
	}
	return instance;
}

Game::~Game()
{
	if(DEBUG)
		std::cout<<"deleting game \n";

	//if(DEBUG)
		//std::cout<<"deleting graphics \n";
	//delete graphics;
	//if(DEBUG)
		//std::cout<<"deleting text \n";
	//delete text;
	//instance=NULL;
}

int Game::initGame()
{
	switch(graphMode)
	{
	    case SDL:
		if(DEBUG)
			cout<<"SDL graphics mode\n";
		this->graphics=new GraphicsSDL();
		break;
	    case OGL:
		if(DEBUG)
			cout<<"OpenGL graphics mode\n";
		this->graphics=new GraphicsGL();
		break;
	}
	text=graphics->loadTexture("/home/mage/Pictures/GameSprites/res/magusSheet.png");
	if(text==NULL)
	{
		std::cout<<"loadTexture fail "<<endl;
		return 1;
	}
	return 0;
}
void Game::mainGameLoop()
{
	bool quit=false;
	Timer fps;
	while(!quit)
	{
		fps.start();
		if(DEBUG)
			cout<<"begin main game loop\n";
		while(SDL_PollEvent(&event))//polling
		{

			if(DEBUG)
			    cout<<"event type "<<event.type<<endl;
			if(event.type==SDL_QUIT)//exit flag
			{
				cout<<"exiting\n";
				quit=true;		
			}
		}
		
		if(DEBUG)
			cout<<"update\n";
		update();
		if(DEBUG)
			cout<<"render\n";
		render();	
		if( fps.get_ticks() < 1000 / FPS ) 
		{
			 SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() ); 
		}
		if(DEBUG_FPS)
			cout<<"runing at "<<1000/fps.get_ticks()<<endl;
	
	}
}

void Game::update()
{
}


void Game::render()
{ 
	
	this->graphics->render(text);
}

Graphics* Game::getGraphics()
{
	return this->graphics;
}
