#ifndef SPIRTESHEET_H
#define SPIRTESHEET_H

#include <string>
#include <vector>
#include <iostream>
#include "Graphics.h"
#include "Texture.h"
class Texture;
class SpriteSheet
{
    protected:
	Texture* map;
	Rects render_rect;
	vector<Rects*> *mesh;
	int frame;
    public:
	SpriteSheet(std::string  name);
	~SpriteSheet();
	void addRect(Rects *rect);
	void setFrame(int frame);
	Texture* getTexture()
	{
	    return map;
	};
	Rects* getFrameRect();
	
};




#endif
