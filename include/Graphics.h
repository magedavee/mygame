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

#include "Graphics.h"
#include "Game.h"
#include "SDLINC.h"
#include "Texture.h"

class Game;
class Texture;
class Graphics
{
protected:
	SDL_Window* screen;
	SDL_GLContext context;
	Uint32 getPixel(SDL_Surface *surface,int x,int y);
	vector<Rects> rectList;
public:
	static bool DEBUG;
	Graphics();
	virtual ~Graphics();
	bool init();
	bool initGL();
	void render();
	bool isBigEndian(){return SDL_BYTEORDER == SDL_BIG_ENDIAN;};
//texture functions;
	Texture* loadTexture(std::string filename);
	void bindTexture(Texture* texture);
	void unbindTexture();
	void freeTexture(Texture* texture);
	bool updateTexture(Texture *);
	void addTexture(Texture *,Rects *);


	void enableTransparency()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	};
};

#endif 
