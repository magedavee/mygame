#ifndef OBJ_H
#define OBJ_H

#include "SpriteSheet.h"
#include "Game.h"
#include "Plugin.h"
#include <string>
#include <vector>
class SpriteSheet;
class Game;
class Object
{
    protected:
	Game * game;
	vector<SpriteSheet> Sprites;
    public:
	Object(string){};
	virtual void update(){};
	virtual void render(){};
};
class VObjectPlugin
{
    public:
	virtual void render(Object&)=0;
	virtual void update(Object)=0;
};
class VObjectPluginRegistrar 
{
    public:        
	virtual std::  unique_ptr<VObjectPlugin> getPlugin() = 0;
};    
class ObjectPluginFactory 
{
    private:
	std::map<std::string, VObjectPluginRegistrar*> registry_;
	ObjectPluginFactory(): registry_() {};
	ObjectPluginFactory(ObjectPluginFactory const&) =delete;
	void operator=(ObjectPluginFactory const&)=delete ;
    public:
	static ObjectPluginFactory& getInstance()
	{

	    static ObjectPluginFactory instance;
	    return instance;
	};
	void registerClass(VObjectPluginRegistrar * registrar,std::string name)
	{
	    registry_[name] = registrar;
	        /* throws out_of_range if plugin unknown */
	};
	std::  unique_ptr<VObjectPlugin> getPlugin(std::string name) 
	{
	    VObjectPluginRegistrar* registrar = registry_.at(name);
	    return registrar->getPlugin();
	}
};
#endif
