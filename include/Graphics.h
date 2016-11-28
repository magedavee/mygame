#include <string>
#include <vector>
#include <utility>
#include <stdint.h>
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

#endif 
