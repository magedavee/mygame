#ifndef PLUGIN_HH
#define PLUGIN_HH
#include <libconfig.h++>
#include <string>
#include <map>
#include <memory>
/*
   The default plugin which all pluging should derive from.
*/
class VPlugin
{
    protected:
    public:
};


class VPluginRegistrar 
{
    public:        
	virtual std::  shared_ptr<VPlugin> getPlugin() = 0;
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
	std::shared_ptr<VPlugin> getPlugin(std::string name);
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
	std::shared_ptr<VPlugin> getPlugin()
	{
	    std::shared_ptr<VPlugin> plugin(new TPlugin());
	    return plugin;
	};
    private:
	std::string classname_;
};

template<class TPlugin>
class PluginRegistrarSingleton:VPluginRegistrar
{
    std::shared_ptr<VPlugin> plugin;
    public:
	PluginRegistrarSingleton(std::string classname): classname_(classname),plugin(new TPlugin())
	    {
		PluginFactory &factory = PluginFactory::getInstance();
		factory.registerClass(this, classname);
	    };
	std::shared_ptr<VPlugin> getPlugin()
	{
	    return plugin;
	};
    private:
	std::string classname_;
};

#define REGISTER_PLUGIN(CLASSNAME) \
	namespace { \
	    static PluginRegistrar<CLASSNAME> \
	    _registrar( #CLASSNAME ); \
    };

#endif
