#include <string>
#include <vector>
#include <stdint.h>
using namespace std;
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Graphics.h"
#include "Game.h"
#include "OGL.h"
#include "SDLINC.h"
#include "Texture.h"

struct Vertex
{
	GLfloat x,y;
};
struct Quad
{
	Vertex v[4];
};
class Game;
class Texture;
class Graphics
{
protected:
	SDL_Window* screen;
	SDL_GLContext context;
	Uint32 getPixel(SDL_Surface *surface,int x,int y);
public:
	static bool DEBUG;
	Graphics();
	virtual ~Graphics();
	bool init();
	bool initGL();
//	void applySurface(int x, int y,Texture* texture);
//	GLuint loadTexture(char *filename,int *textw,int *texth);
//	bool textureLoad(SDL_Texture * tex,string * name);
	void render();

	bool isBigEndian(){return SDL_BYTEORDER == SDL_BIG_ENDIAN;};
//texture functions;
	Texture* loadTexture(std::string filename);
	void bindTexture(Texture* texture);
	void unbindTexture();
	void freeTexture(Texture* texture);
	bool updateTexture(Texture *texture);


	void enableTransparency()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	};
};

#endif 
