#include "Object.h"


ObjectFactory&ObjectFactory::getInstance()
{

    static ObjectFactory instance;
    return instance;
};


