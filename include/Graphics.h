#include <string>
#include <vector>
#include <stdint.h>
#include "OGL.h"
using namespace std;
#ifndef GEOSTRUCT
#define GEOSTRUCT

struct Vertex
{
	GLfloat x,y;
};
struct Quad
{
	Vertex v[4];
};
struct Rects
{
    GLfloat x,y,h,w;
};
#endif
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Game.h"
#include "SDLINC.h"
#include "Texture.h"

class Game;
class Texture;
class Graphics
{
protected:
	SDL_Window* window;
	SDL_GLContext context;
	Uint32 getPixel(SDL_Surface *surface,int x,int y);
	vector<Rects> rectList;
	SDL_Renderer* gRenderer;
public:
	static bool DEBUG;
	Graphics(){};
	virtual ~Graphics(){};
	virtual bool init()=0;
	virtual void render(Texture* text)=0;
	virtual bool isBigEndian()=0;
//texture functions;
	virtual Texture* loadTexture(std::string filename)=0;
	virtual void freeTexture(Texture* texture)=0;
	virtual bool updateTexture(Texture *)=0;
	virtual void addTexture(Texture *,Rects *)=0;


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
	void render(Texture* text);
	bool isBigEndian(){return SDL_BYTEORDER == SDL_BIG_ENDIAN;};
//texture functions;
	Texture* loadTexture(std::string filename);
	void freeTexture(Texture* texture);
	bool updateTexture(Texture *);
	void addTexture(Texture *,Rects *);


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
	void render(Texture* text);
//texture functions;
	bool isBigEndian(){return SDL_BYTEORDER == SDL_BIG_ENDIAN;};
	Texture* loadTexture(std::string filename);
	void freeTexture(Texture* texture);
	bool updateTexture(Texture *);
	void addTexture(Texture *,Rects *);


};

#endif 
