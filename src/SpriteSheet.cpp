#include "SpriteSheet.h"
#include "Game.h"
#include <string>

SpriteSheet::SpriteSheet(string name)
{
    Game* game=Game::getInstance();
    this->map=game->getGraphics()->loadTexture(name.c_str());
    this->render_rect.x=0;
    this->render_rect.y=0;
    this->render_rect.h=0;
    this->render_rect.w=0;
    this->mesh=new vector<Rects*>();
    frame=0;
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::addRect(Rects *rect)
{
    this->mesh->push_back(rect);
}

void SpriteSheet::setFrame(int frame)
{
    this->frame=frame;
}
