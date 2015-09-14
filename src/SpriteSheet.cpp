#include "SpriteSheet.h"
#include "Game.h"
#include <string>

SpriteSheet::SpriteSheet(string* name)
{
    Game* game=Game::getInstance();
    this->map=game->getGraphics()->loadTexture(name->c_str());
    this->render_rect.x=0;
    this->render_rect.y=0;
    this->render_rect.h=0;
    this->render_rect.w=0;
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::bind()
{
    this->map->bind();
}
