#ifndef SPIRTEMAP_H
#define SPIRTEMAP_H

#include <string>
#include <vector>
#include "Graphics.h"
#include "Texture.h"
class Texture;
class SpriteMap
{
    protected:
	Texture* map;
	Rects render_rect;
	vector<Rects> mesh;
    public:
	SpriteMap(std::string * name);
	~SpriteMap();
	void bind();
};




#endif
