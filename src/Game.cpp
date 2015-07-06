#include <string>

#include "SDLINC.h"
#include <iostream>
#include <string>
#include "Game.h"
#include "Attributes.h"
#include "Graphics.h"
#include "Timer.h"
#include "SpriteMap.h"


//#define DEBUG false//||DEBUG_ALL //set to true to turn on debug for this class only
//#define DEBUG_FPS false||DEBUG //set to true to see fram per sec output

static Game *  instance=NULL;
bool Game::DEBUG=false;
bool Game::DEBUG_ALL=false;
bool Game::DEBUG_FPS=false;
bool Game::DEBUG_GRAPHICS=false;
Game::Game()
{
	argc=0;
	
	
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
		std::cout<<"game \n";
	delete graphics;
	delete text;
	instance=NULL;
}

int Game::initGame()
{

	this->graphics=new Graphics();
	string* name=new string("/home/mage/Pictures/GameSprites/res/magusSheet.png");
	text=graphics->loadTexture("/home/mage/Pictures/GameSprites/res/magus.png");
	this->sprite=new SpriteMap(name);
	for(int y=0;y<25;++y)
	{
		for(int x=0;x<25;++x)
			text->changePixel(x,y,0xff,0,0,0xff);
	}
	graphics->updateTexture(text);
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
	
//	text->bind();	
	this->sprite->bind();
	this->graphics->render();
}

Graphics* Game::getGraphics()
{
	return this->graphics;
}
