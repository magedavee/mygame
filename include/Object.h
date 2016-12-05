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
    protected:
	Game * game;
	vector<SpriteSheet*>* sprites;
	string plug,id;
	int x,y;
    public:
	Object(string plug);
	virtual void update();
	virtual void render();
	vector<SpriteSheet*>* getSprites();
	string getPluginName(){return plug;};
	string getID(){return id;};
	int getX(){return x;};
	int getY()
	{
	    //cerr<<"db getY"<< y<<endl;
	    return y;
	};
	void setSprites(vector<SpriteSheet*>* sprites)
	{
	    //cerr<<"db setSprites befor "<< sprites<<endl;
	    //cerr<<"db setSprites "<< sprites->size()<<endl;
	    sprites=sprites;
	    //cerr<<"db setSprites after "<< sprites<<endl;
	    //cerr<<"db setSprites "<< sprites->size()<<endl;
	};
	void addSprite(string name);
	void setPluginName(string plug){ plug=plug;};
	void setID(string id){ id=id;};
	void setX(int x){x= x;};
	void setY(int y){y= y;};

};
class VObjectPlugin
{
    public:
	virtual void init(Object*,string)=0;
	virtual void render(Object*)=0;
	virtual void update(Object*)=0;
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
	static ObjectPluginFactory& getInstance();
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
template<class TPlugin>
class ObjectPluginRegistrar:VObjectPluginRegistrar 
{
    public:
	ObjectPluginRegistrar(std::string classname): classname_(classname)
	    {
		ObjectPluginFactory &factory = ObjectPluginFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::unique_ptr<VObjectPlugin> getPlugin()
	{
	    std::unique_ptr<VObjectPlugin> plugin(new TPlugin());
	    return plugin;
	};
    private:
	std::string classname_;
};
#define REGISTER_OBJECT(CLASSNAME) \
	namespace { \
	    static ObjectPluginRegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };
#endif
