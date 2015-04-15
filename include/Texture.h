#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <stdint.h>
#include "Graphics.h"
class Texture
{
    public:
        Texture();

        ~Texture();




        void render();

        uint32_t getID();
        void  setID(int id);

        int getWidth();
	void setWidth(int w);

	int getMode();
	void setMode(int mode);

	int getBPP();
	void setBPP(int bpp);

        int getHeight();
	void setHeight(int h);
	SDL_Surface* getSurface();
	GLuint* getPixels();
	void setPixels(GLuint*  mPixels);
	uint32_t getSize();
	void changePixel(int x,int y,uint8_t r,uint8_t  g,uint8_t b,uint8_t a );
		
    private:
        //Texture name
        uint32_t textureID;
	//pixils
	uint32_t* mPixels;

	uint32_t size;
        //Texture dimensions
        int textureWidth;
        int textureHeight;
	int mode;
	int bpp;
	void setSize();
};

#endif
