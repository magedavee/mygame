#ifndef MAGUS
#define MAGUS
#include"Object.h"
class Magus:public VObjectPlugin
{
    public:
	void init(Object*,string);
	void update(Object*);
	void render(Object*);
};
#endif
