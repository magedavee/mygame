#include <string>
#include <stdint.h>
#include "Attributes.h"
#include "Graphics.h"
#include "SpriteSheet.h"
#include <iostream>

REGISTER_GRAPHICS(GraphicsSDL)
GraphicsSDL::GraphicsSDL()
{
/*	glutInit( &argc, args );
	 //Create OpenGL 2.1 context
        glutInitContextVersion( 2, 1 );

        //Create Double Buffered Window
        glutInitDisplayMode( GLUT_DOUBLE );
        glutInitWindowSize( SCREENWIDTH, SCREENHEIGHT );
        glutCreateWindow( "OpenGL" );
*/
    //GLuint gVertexBuffer = 0;
    //if(!this->init())
    //{
	    ////cerr<<"db "<<"failed init of graphics.\n";
    //}
    //else
    //{
	////cerr<<"db "<<"graphics ok\n";
    //}
}

GraphicsSDL::~GraphicsSDL()
{
}


bool GraphicsSDL::init()
{
    //cerr<<"db "<<"initlizing GraphicsSDL\n";
     	if( SDL_Init(SDL_INIT_VIDEO)<0)
        {
                //cerr<<"db "<<"sdl init fail\n";
                return false;
        }
    
	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
	    //cerr<<"db "<<"Warning: Linear texture filtering not enabled!"<<endl;
	}



	window =SDL_CreateWindow( "My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	if(this->window==NULL)
	{
		//cerr<<"db "<<"window null SDL Error: "<<SDL_GetError()<<endl;
		return false;
	}
      //Initialize PNG loading
	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL ) 
	{ 
	    //cerr<<"db "<< "Renderer could not be created! SDL Error "<<SDL_GetError()<<endl; 
	    return false; 
	}

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
	{ 
		//cerr<<"db "<< "SDL_image could not initialize! SDL_image Error: "<< IMG_GetError() <<endl; 
		return false; 
	}
	//cerr<<"db "<<"Image Flags: "<<imgFlags<<endl; 
	
	//cerr<<"db "<<"Finish with initilizing graphics\n";
        return true;
}


void GraphicsSDL::render(Texture* text,Rects* src,Rects* dst )
{
    //cerr<<"db GraphicsSDL\n";
    SDL_Rect  sR={src->x,src->y,src->w,src->h};
    SDL_Rect  dR={dst->x,dst->y,dst->w,dst->h};
    //Clear screen
    SDL_RenderClear( gRenderer );

    //Render texture to screen
    SDL_RenderCopy( gRenderer,text->getSDL() , &sR,&dR );

    //Update screen
    SDL_RenderPresent( gRenderer );
    //SDL_GL_SwapWindow( window );
}	



Texture* GraphicsSDL::loadTexture(std::string filename)
{
    Texture *text=new Texture();
    
    SDL_Texture* newTexture = NULL;
    //Load image at specified path 
    SDL_Surface* loadedSurface = IMG_Load( filename.c_str() ); 
    if( loadedSurface == NULL ) 
    { 
	//cerr<<"db "<<"Unable to load image "<<filename<<"! SDL_image Error:"<< IMG_GetError()<<endl;
    } 
    else 
    { 
	//Create texture from surface pixels 
	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); 
	if( newTexture == NULL ) 
	{ 
	    //cerr<<"db "<<"Unable to create texture from"<<filename<< "SDL Error: "<<SDL_GetError()<<endl; 
	} //Get rid of old loaded surface 
	SDL_FreeSurface( loadedSurface ); 
    }
    text->setSDL(newTexture);
    return text;
}

void GraphicsSDL::freeTexture(Texture *texture)
{
        //Delete texture
        if( texture->getSDL()!= NULL )
        {
	    SDL_DestroyTexture(texture->getSDL());
	    texture->setSDL(NULL);
        }

        texture->setWidth(0);
        texture->setHeight(0);
}

Uint32 GraphicsSDL::getPixel(SDL_Surface *surface, int x,int y)
{
	int bpp=0;
	if(x>=0&&y>=0&&x<surface->w&&y<surface->h)
	{
		bpp=surface->format->BytesPerPixel;
	}
	else
	{
		//cerr<<"db "<<"x= "<<x<<" y ="<<y<<" is out of bounds\n";
		return 0;
	}
	Uint8 *p=(Uint8*)surface->pixels+y*surface->pitch+x*bpp;
	switch(bpp) 
	{
	    case 1:
		return *p;
		break;

	    case 2:
		return *(Uint16 *)p;
		break;

	    case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		    return p[0] << 16 | p[1] << 8 | p[2];
		else
		    return p[0] | p[1] << 8 | p[2] << 16;
		break;

	    case 4:
		return *(Uint32 *)p;
		break;

	    default:
		//cerr<<"db "<<"Error in reading pixel at x="<<x<<" y="<<y<<endl;
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}



bool GraphicsSDL::updateTexture(Texture* texture)
{
	
	return true;
}

void GraphicsSDL::addTexture(Texture *texture,Rects *clip)
{

}

void GraphicsSDL::addSprite(SpriteSheet* sprite)
{
    pair<Texture*,Rects*> renderPair(sprite->getTexture(),sprite->getFrameRect());
    this->renderList->push_back(renderPair);
}
