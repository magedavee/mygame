#include <iostream>
#include"Pixel.h"
#include "Game.h"

Pixel::Pixel()
{
	r=0;
	g=0;
	b=0;
	a=0;
	pixel=0;
}

Pixel::Pixel(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{
	r=r;
	g=g;
	b=b;
	a=a;
	
}

Pixel::Pixel(Pixel &pixel)
{
	r=pixel.r;
        g=pixel.g;
	b=pixel.b;
	a=pixel.a;
}
