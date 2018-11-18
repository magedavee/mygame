#ifndef RTE_HH
#define RTE_HH
#include "Plugin.h"
#include <libconfig.h++>
#include <string>
#include <map>
#include <memory>
/*RTE run time environment plugins. Used to create game runtime environments 
  such as the game itself or any other edit modes. 
  */
class VRTE:public VPlugin
{
    protected:
    public:
        virtual void run()=0;
};
class VRTERegistrar
 
{
    public:        
	virtual std::  unique_ptr<VRTE> getRTE() = 0;
};    
class RTEFactory 
{
    private:
	std::map<std::string, VRTERegistrar*> registry_;
	RTEFactory(): registry_() {};
	RTEFactory(RTEFactory const&) =delete;
	void operator=(RTEFactory const&)=delete ;
    public:
	static RTEFactory& getInstance();
	void registerClass(VRTERegistrar * registrar,std::string name);
	std::unique_ptr<VRTE> getRTE(std::string name);
};
template<class TRTE>
class RTERegistrar:VRTERegistrar
{
    public:
	RTERegistrar(std::string classname): classname_(classname)
	    {
		RTEFactory &factory = RTEFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::unique_ptr<VRTE> getRTE()
	{
	    std::unique_ptr<VRTE> plugin(new TRTE());
	    return plugin;
	};
    private:
	std::string classname_;
};
template<class TRTE>
class RTERegistrarSingleton:VRTERegistrar
{
    std::shared_ptr<VRTE> plugin;
    public:
	RTERegistrarSingleton(std::string classname): classname_(classname),plugin(new TRTE())
	    {
		RTEFactory &factory = RTEFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::shared_ptr<VRTE> getRTE()
	{
	    return plugin;
	};
    private:
	std::string classname_;
};
#define REGISTER_RTE(CLASSNAME) \
	namespace { \
	    static RTERegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };


#endif
