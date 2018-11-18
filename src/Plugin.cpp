#include"Plugin.h"

PluginFactory& PluginFactory::getInstance()
{
    static PluginFactory instance;
    return instance;
}
void PluginFactory::registerClass(VPluginRegistrar* registrar, std::string name) 
{
    registry_[name] = registrar;
}
std::shared_ptr<VPlugin> PluginFactory::getPlugin(std::string name) 
{
	    /* throws out_of_range if plugin unknown */
    VPluginRegistrar* registrar = registry_.at(name);
    return registrar->getPlugin();
}


