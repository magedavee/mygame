#include"Event.h"

EventFactory& EventFactory::getInstance()
{
    static EventFactory instance;
    return instance;
}
void EventFactory::registerClass(VEventRegistrar* registrar, std::string name) 
{
    registry_[name] = registrar;
}
std::shared_ptr<Event> EventFactory::getEvent(std::string name) 
{
	    /* throws out_of_range if plugin unknown */
    VEventRegistrar* registrar = registry_.at(name);
    return registrar->getEvent();
}
