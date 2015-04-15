#include <stdint.h>
#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	uint8_t r,g,b,a;
	uint32_t pixel;
	int bbp;
	uint32_t format;
public:
	Pixel();
	Pixel(uint8_t,uint8_t,uint8_t,uint8_t);
	Pixel(Pixel& pixel);
	~Pixel();
	Pixel & operator = (const Pixel & other)
	{
		if(this != &other)
		{
			r=other.r;
			g=other.g;
			b=other.b;
			a=other.a;
		}
		return *this;
		
	};
	void setRGBA(uint8_t,uint8_t,uint8_t,uint8_t);
	uint32_t getPixel(){return pixel;};
	
};

#endif 
