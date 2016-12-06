#ifndef OBJ_H
#define OBJ_H

#include "SpriteSheet.h"
#include "Game.h"
#include "Plugin.h"
#include "Graphics.h"
#include <string>
#include <vector>
class SpriteSheet;
class Game;
class Object
{
    public:
	virtual void update()=0;
	virtual void render()=0;

};
class VObjectRegistrar 
{
    public:        
	virtual std::  shared_ptr<Object> getPlugin() = 0;
};    
class ObjectFactory 
{
    private:
	std::map<std::string,VObjectRegistrar*> registry_;
	ObjectFactory(): registry_() {};
	ObjectFactory(ObjectFactory const&) =delete;
	void operator=(ObjectFactory const&)=delete ;
    public:
	static ObjectFactory& getInstance();
	void registerClass(VObjectRegistrar * registrar,std::string name)
	{
	    registry_[name] = registrar;
	        /* throws out_of_range if plugin unknown */
	};
	std::shared_ptr<Object> getPlugin(std::string name) 
	{
	    VObjectRegistrar* registrar = registry_.at(name);
	    return registrar->getPlugin();
	}
};
template<class TPlugin>
class ObjectRegistrar:VObjectRegistrar 
{
    public:
	ObjectRegistrar(std::string classname): classname_(classname)
	    {
		ObjectFactory &factory = ObjectFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::shared_ptr<Object> getPlugin()
	{
	    std::shared_ptr<Object> plugin(new TPlugin());
	    return plugin;
	};
    private:
	std::string classname_;
};
#define REGISTER_OBJECT(CLASSNAME) \
	namespace { \
	    static ObjectRegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };
#endif
