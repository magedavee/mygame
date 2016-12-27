#include"EventHandler.h"

EventHandlerFactory& EventHandlerFactory::getInstance()
{
    static EventHandlerFactory instance;
    return instance;
}
void EventHandlerFactory::registerClass(VEventHandlerRegistrar* registrar, std::string name) 
{
    registry_[name] = registrar;
}
std::shared_ptr<EventHandler> EventHandlerFactory::getEventHandler(std::string name) 
{
	    /* throws out_of_range if plugin unknown */
    VEventHandlerRegistrar* registrar = registry_.at(name);
    return registrar->getEventHandler();
}
