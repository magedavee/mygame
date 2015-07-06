#include <stdint.h>
#include "Texture.h"
#include "Attributes.h"
#include <iostream>
#include "Game.h"

Texture::Texture()
{
	textureID=0;
	textureWidth=0;
	textureHeight=0;
	mode=0;
	bpp=0;
	mPixels=NULL;
	 

}

Texture::~Texture()
{
	Game::getInstance()->getGraphics()->freeTexture(this);
	delete[]  mPixels;
}


void Texture::bind()
{
	Game::getInstance()->getGraphics()->bindTexture(this);
}

uint32_t Texture::getID()
{
	return textureID;
}

int Texture::getWidth()
{
	return textureWidth;
}

int Texture::getHeight()
{
	return textureHeight;
}

int Texture::getMode()
{
	return mode;
}

int Texture::getBPP()
{
	return bpp;
}

void Texture::setID(int id)
{
	textureID=id;
}


void Texture::setWidth(int w)
{
	textureWidth=w;
	setSize();
}

void Texture::setHeight(int h)
{
	textureHeight=h;
	setSize();
}

void Texture::setMode(int mode)
{
	this->mode=mode;
}

void Texture::setBPP(int bpp)
{
	this->bpp=bpp;
}

uint32_t* Texture::getPixels()
{
	return mPixels;
}


void Texture::setPixels( uint32_t * mPixels )
{
	this->mPixels=mPixels;
}


uint32_t Texture::getSize()
{
	return size;
}

void Texture::setSize()
{
	size=textureHeight*textureWidth;
}


void Texture::changePixel(int x,int y,uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{
	if(x<0||x>textureWidth||y<0||y>textureHeight)
	{
		cout<<"x and/or y is out bounds x="<<x<<" y="<<y<<endl;
		return;
	}
	uint32_t *pixel=mPixels+(x+y*textureWidth);

	int index=x+y*textureWidth;
	uint32_t R=(uint32_t)r;
	uint32_t G=(uint32_t)g;
	uint32_t B=(uint32_t)b;
	uint32_t A=(uint32_t)a;
	*pixel=(A<<24)+(B<<16)+(G<<8)+R;
		
	mPixels[index]=*pixel;
}
