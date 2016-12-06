#include"Graphics.h"
using namespace std;
GraphicsFactory& GraphicsFactory::getInstance()
{
    static GraphicsFactory instance;
    return instance;
}
void GraphicsFactory::registerClass(VGraphicsRegistrar* registrar, std::string name) 
{
    registry_[name] = registrar;
}
std::shared_ptr<Graphics> GraphicsFactory::getPlugin(std::string name) 
{
	    /* throws out_of_range if plugin unknown */
    //cerr<<"db. GraphicsFactory::getPlugin registry \n";
    VGraphicsRegistrar* registrar = registry_.at(name);
    //cerr<<"db. GraphicsFactory::getPlugin return \n";
    return registrar->getPlugin();
}
