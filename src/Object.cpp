#include "Object.h"

void Object::update()
{
}

void Object::render()
{
}
ObjectPluginFactory&ObjectPluginFactory::getInstance()
{

    static ObjectPluginFactory instance;
    return instance;
};
