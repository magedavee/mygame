#include"RTE.h"
#include"Plugin.h"

RTEFactory& RTEFactory::getInstance()
{
    static RTEFactory instance;
    return instance;
}
void RTEFactory::registerClass(VRTERegistrar* registrar, std::string name) 
{
    registry_[name] = registrar;
}
std::unique_ptr<VRTE> RTEFactory::getRTE(std::string name) 
{
	    /* throws out_of_range if plugin unknown */
    VRTERegistrar* registrar = registry_.at(name);
    return registrar->getRTE();
}


