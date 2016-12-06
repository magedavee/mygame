#include <string>
#include <vector>
#include <memory>
#include <map>
#include <utility>
#include <stdint.h>
#include <iostream>
#include "OGL.h"
#include "SpriteSheet.h"
using namespace std;
#ifndef GEOSTRUCT
#define GEOSTRUCT

 typedef struct 
{
	GLfloat x,y;
}Vertex;
typedef struct 
{
	Vertex v[4];
}Quad;
typedef struct 
{
    int x,y,h,w;
}Rects;
#endif
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Game.h"
#include "SDLINC.h"
#include "Texture.h"
using namespace std;
class Game;
class Texture;
class SpriteSheet;
class Graphics
{
protected:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 getPixel(SDL_Surface *surface,int x,int y);
	vector<Rects> rectList;
	SDL_Renderer* gRenderer;
	vector<pair<Texture*,Rects*>> *renderList;
public:
	Graphics(){};
	virtual ~Graphics(){};
	virtual bool init()=0;
	virtual void render(Texture*,Rects*,Rects*)=0;
	virtual bool isBigEndian()=0;
//texture functions;
	virtual Texture* loadTexture(std::string filename)=0;
	virtual void freeTexture(Texture* texture)=0;
	virtual bool updateTexture(Texture *)=0;
	virtual void addTexture(Texture *,Rects *)=0;
	virtual void addSprite(SpriteSheet* sprite)=0;


};
class VGraphicsRegistrar 
{
    public:        
	virtual std::  shared_ptr<Graphics> getPlugin() = 0;
};    
class GraphicsFactory 
{
    private:
	std::map<std::string, VGraphicsRegistrar*> registry_;
	GraphicsFactory(): registry_() {};
	GraphicsFactory(GraphicsFactory const&) =delete;
	void operator=(GraphicsFactory const&)=delete ;
    public:
	static GraphicsFactory& getInstance();
	void registerClass(VGraphicsRegistrar * registrar,std::string name);
	std::shared_ptr<Graphics> getPlugin(std::string name);
};
template<class TPlugin>
class GraphicsRegistrar:VGraphicsRegistrar
{
    public:
	GraphicsRegistrar(std::string classname): classname_(classname)
	    {
		GraphicsFactory &factory = GraphicsFactory::getInstance();
		//cerr<<"db. GraphicsRegistrar classname  "<<classname_<<endl;
		factory.registerClass(this, classname);
	    };
	std::shared_ptr<Graphics> getPlugin()
	{
	    std::shared_ptr<Graphics> plugin(new TPlugin());
	    //cerr<<"db new graphics "<<plugin<<endl;
	    return plugin;
	};
    private:
	std::string classname_;
};

class GraphicsSDL:public Graphics
{
protected:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 getPixel(SDL_Surface *surface,int x,int y);
	vector<Rects> rectList;
	SDL_Renderer* gRenderer;
public:
	GraphicsSDL();
	virtual ~GraphicsSDL();
	bool init();
	void render(Texture* text,Rects*,Rects*);
	bool isBigEndian(){return SDL_BYTEORDER == SDL_BIG_ENDIAN;};
//texture functions;
	Texture* loadTexture(std::string filename);
	void freeTexture(Texture* texture);
	bool updateTexture(Texture *);
	void addTexture(Texture *,Rects *);
	void addSprite(SpriteSheet* sprite);


};

class GraphicsGL: public Graphics
{
protected:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 getPixel(SDL_Surface *surface,int x,int y);
	vector<Rects> rectList;
	bool initGL();
	void enableTransparency()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	};
	void unbindTexture();
	void bindTexture(Texture* texture);
public:
	GraphicsGL();
	virtual ~GraphicsGL();
	bool init();
	void render(Texture* text,Rects*,Rects*);
//texture functions;
	bool isBigEndian(){return SDL_BYTEORDER == SDL_BIG_ENDIAN;};
	Texture* loadTexture(std::string filename);
	void freeTexture(Texture* texture);
	bool updateTexture(Texture *);
	void addTexture(Texture *,Rects *);
	void addSprite(SpriteSheet* sprite);


};
#define REGISTER_GRAPHICS(CLASSNAME) \
	namespace { \
	    static GraphicsRegistrar<CLASSNAME> \
	    graphics_registrar( #CLASSNAME ); \
    };

#endif

