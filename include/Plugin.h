#ifndef DYNAMICPLUGINSAVER_HH
#define DYNAMICPLUGINSAVER_HH
#include <libconfig.h++>
#include <string>
#include <map>
#include <memory>
namespace PluginSystem
{
    class VPlugin
    {
	public:
	    virtual void update()=0;
    };
    class VPluginRegistrar 
    {
	public:        
	    virtual std::  unique_ptr<VPlugin> getPlugin() = 0;
    };    
    class PluginFactory 
    {
	private:
	    std::map<std::string, VPluginRegistrar*> registry_;
	    PluginFactory(): registry_() {};
	    PluginFactory(PluginFactory const&) =delete;
	    void operator=(PluginFactory const&)=delete ;
	public:
	    static PluginFactory& getInstance();
	    void registerClass(VPluginRegistrar * registrar,std::string name);
	    std::unique_ptr<VPlugin> getPlugin(std::string name);
    };
    template<class TPlugin>
    class PluginRegistrar:VPluginRegistrar
    {
	public:
	    PluginRegistrar(std::string classname): classname_(classname)
		{
		    PluginFactory &factory = PluginFactory::getInstance();
		    factory.registerClass(this, classname);
		};
	    std::unique_ptr<VPlugin> getPlugin()
	    {
		std::unique_ptr<VPlugin> plugin(new TPlugin());
		return plugin;
	    };
	private:
	    std::string classname_;
    };}
#define REGISTER_PLUGIN(CLASSNAME) \
	namespace { \
	    static PluginSystem::PluginRegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };

#endif
