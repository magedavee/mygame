#ifndef SPIRTESHEET_H
#define SPIRTESHEET_H

#include <string>
#include <vector>
#include "Graphics.h"
#include "Texture.h"
class Texture;
class SpriteSheet
{
    protected:
	Texture* map;
	Rects render_rect;
	vector<Rects> mesh;
    public:
	SpriteSheet(std::string * name);
	~SpriteSheet();
};




#endif
