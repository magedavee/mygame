#include "Object.h"

Object::Object(string plug):plug(plug),x(0),y(0)
{
    auto& factory=ObjectPluginFactory::getInstance();
    auto plugin=factory.getPlugin("Magus");
    plugin->init(this,"");

};
void Object::update()
{
    auto& factory=ObjectPluginFactory::getInstance();
    auto plugin=factory.getPlugin("Magus");
    plugin->update(this);
}

void Object::render()
{
    auto& factory=ObjectPluginFactory::getInstance();
    auto plugin=factory.getPlugin("Magus");
    plugin->render(this);
}
ObjectPluginFactory&ObjectPluginFactory::getInstance()
{

    static ObjectPluginFactory instance;
    return instance;
};
vector<SpriteSheet*>* Object::getSprites()
{
    //cerr<<"db getSprites "<< sprites<<endl;
    //cerr<<"db getSprites "<< sprites->size()<<endl;
    return sprites;
};

void Object::addSprite(string name)
{
    if(!sprites)
    {
	//cerr<<"db. new sprite map vector \n";
	sprites=new vector<SpriteSheet*>();
    }
    //cerr<<"db. new sprite map "<<name<<endl;
    sprites=new vector<SpriteSheet*>();
    sprites->push_back(new SpriteSheet(name));
}


