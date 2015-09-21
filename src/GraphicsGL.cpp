#include <string>
#include <stdint.h>
#include "Attributes.h"
#include <iostream>
#include "Graphics.h"
//#define DEBUG false||DEBUG_ALL

bool GraphicsGL::DEBUG = DEBUG=Graphics::DEBUG_GRAPHICS||Game::DEBUG_ALL;

GraphicsGL::GraphicsGL()
{
/*	glutInit( &argc, args );
	 //Create OpenGL 2.1 context
        glutInitContextVersion( 2, 1 );

        //Create Double Buffered Window
        glutInitDisplayMode( GLUT_DOUBLE );
        glutInitWindowSize( SCREENWIDTH, SCREENHEIGHT );
        glutCreateWindow( "OpenGL" );
*/
    cout<<"this OGL\n";
    if(DEBUG)
	    cout<<"DEBUG is on in GraphicsGL\n";
    //GLuint gVertexBuffer = 0;
    //if(!this->init())
    //{
	    //std::cout<<"failed init of graphics.\n";
    //}
    //else
    //{
	    //if(DEBUG)
	    //std::cout<<"graphics ok\n";
    //}
    //void EnableTransparency();
}

GraphicsGL::~GraphicsGL()
{
}


bool GraphicsGL::init()
{
	if(DEBUG)
		std::cout<<"initlizing GraphicsGL\n";
     	if( SDL_Init(SDL_INIT_VIDEO)<0)
        {
                std::cout<<"sdl init fail\n";
                return false;
        }
     
    
   
       // window = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_OPENGL );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
//	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	window =SDL_CreateWindow( "My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

        if(this->window==NULL)
        {
                std::cout<<"window null SDL Error: "<<SDL_GetError()<<endl;
                return false;
        }
  //Initialize PNG loading

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
	{ 
		std::cout<< "SDL_image could not initialize! SDL_image Error: "<< IMG_GetError() <<endl; 
		return false; 
	}
	else
	{
		if(DEBUG)
		{
			std::cout<<"Image Flags: "<<imgFlags<<endl; 
		}
	}	
	context= SDL_GL_CreateContext(window);
	if(context==NULL)
	{
		cout<<"OpenGL context could not be created SDL Error:"<<SDL_GetError()<<endl;
		return false;
	}
	if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
		cout<<"Warning Unable to set VSync:"<<SDL_GetError()<<endl;
	}
	//Initialize OpenGL 
	if(DEBUG)
		std::cout<<"initlizing OpenGL\n";
	if( initGL() == false ) 
	{
		std::cout<<"error with opengl\n";
		return false; 
	}
	
	if(DEBUG)
		std::cout<<"Finish with initilizing graphics\n";
  
        return true;
}

bool GraphicsGL::initGL()
{
    glViewport( 0.f, 0.f, SCREENWIDTH, SCREENHEIGHT ); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0.0, SCREENWIDTH, SCREENHEIGHT, 0.0, 1.0, -1.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glEnable( GL_TEXTURE_2D );
    //Set blending 
    glEnable( GL_BLEND ); 
    glDisable( GL_DEPTH_TEST ); 
    glBlendFunc( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    GLenum error=glGetError();
    if(error!=GL_NO_ERROR)
    {
	    std::cout<<"error with open gl init\n";
	    return false;
    }
    return true;
}

void GraphicsGL::render(Texture* text)
{
    bindTexture(text);
    cout<<"this render\n";
/*    Vertex gQuadVertices[ 4 ];
     //Set quad verticies 
    gQuadVertices[ 0 ].x = SCREENWIDTH * 1.f / 4.f; 
    gQuadVertices[ 0 ].y = SCREENHEIGHT * 1.f / 4.f; 
    gQuadVertices[ 1 ].x = SCREENWIDTH * 3.f / 4.f; 
    gQuadVertices[ 1 ].y = SCREENHEIGHT * 1.f / 4.f; 
    gQuadVertices[ 2 ].x = SCREENWIDTH * 3.f / 4.f; 
    gQuadVertices[ 2 ].y = SCREENHEIGHT * 3.f / 4.f; 
    gQuadVertices[ 3 ].x = SCREENWIDTH * 1.f / 4.f; 
    gQuadVertices[ 3 ].y = SCREENHEIGHT * 3.f / 4.f;
    glClear( GL_COLOR_BUFFER_BIT );
     //Enable vertex arrays 
    glEnableClientState( GL_VERTEX_ARRAY );
    //Set vertex data 
    glVertexPointer( 2, GL_FLOAT, 0, gQuadVertices );
    //Draw quad using vertex data 
    glDrawArrays( GL_QUADS, 0, 4 ); 
    //Disable vertex arrays 
    glDisableClientState( GL_VERTEX_ARRAY );*/
    if(DEBUG)
	std::cout<<"Render\n"; 
	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
//    glMatrixMode( GL_TEXTURE );
    glLoadIdentity();
    //Move to center of the window 
    glTranslatef( SCREENWIDTH / 2.f, SCREENHEIGHT / 2.f, 0.f );
    //Render quad
    glBegin( GL_QUADS );
	glTexCoord2f(0, 0);
	glVertex2f( -250.f, -250.f );
	glTexCoord2f(1, 0);
	glVertex2f(  250.f, -250.f );
	glTexCoord2f(1, 1);
	glVertex2f(  250.f,  250.f );
	glTexCoord2f(0,1);
	glVertex2f( -250.f,  250.f );
    glEnd();

	//Update window
    SDL_GL_SwapWindow( window );
}	



Texture* GraphicsGL::loadTexture(std::string filename)
{
	if(DEBUG)
		std::cout<<"loading texture "<<filename.c_str()<<endl;
	Texture * texture=new Texture();
        SDL_Surface* surface = IMG_Load(filename.c_str());

        if (!surface) {

		std::cout<<"surface not loaded "<<filename<<" SDL image Error:"<<IMG_GetError()<<endl;
                return NULL;

        }
        int bpp=surface->format->BytesPerPixel;
	texture->setBPP(bpp);
	int mode=0;
        // work out what format to tell glTexImage2D to use...
        if (surface->format->BytesPerPixel == 3) { // RGB 24bit
			mode=GL_RGB;

        } else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit

                mode=GL_RGBA;

        } else {

                SDL_FreeSurface(surface);
		std::cout<<"format error "<<filename<<endl;
                return NULL;

        }

	texture->setMode(mode);
        texture->setWidth(surface->w);
        texture->setHeight(surface->h);
	GLuint size=texture->getSize();	
	GLuint * mPixels=new GLuint[size];
  //      SDL_LockSurface(surface);
	
	for(int y=0;y<surface->h;++y)
	{
		for(int x=0;x<surface->w;++x)
		{
			int index=x+y*surface->w;
			mPixels[index]=getPixel(surface,x,y);
		}
	}
        // create one texture name
	GLuint textureID;
        glGenTextures(1, &textureID);
	texture->setID(textureID);

        // these affect how this texture is drawn later on...
	SDL_FreeSurface(surface);
	if(texture==NULL)
	{
		std::cout<<"texture failed to load";
	}
	bindTexture(texture);
	if(DEBUG)
		std::cout<<"pixels address: "<<mPixels<<endl;
	if(DEBUG)
		std::cout<<"glTexImage"<<endl;
	int w=texture->getWidth();
	int h=texture->getHeight();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);
        // these affect how this texture is drawn later on...
	if(DEBUG)
		std::cout<<"Texture Parameters"<<endl;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	if(DEBUG)
		std::cout<<"Binding over"<<endl;
	//Check for error 
	GLenum error = glGetError(); 
	if( error != GL_NO_ERROR ) 
	{ 
		cout<< "Error loading texture" <<gluErrorString( error )<<endl;
	} 
	if(DEBUG)
		std::cout<<"texture:  "<<texture<<endl;
	unbindTexture();
	texture->setPixels(mPixels);
	//delete mPixels;
	return texture;
        // tell opengl to use the generated texture name

}

void GraphicsGL::unbindTexture()
{
        glBindTexture(GL_TEXTURE_2D, NULL);
}

void GraphicsGL::bindTexture(Texture * texture)
{
	GLuint textureID=texture->getID();
	if(DEBUG)
		std::cout<<"now binding"<<endl;
        glBindTexture(GL_TEXTURE_2D, textureID);

}
void GraphicsGL::freeTexture(Texture *texture)
{
	GLuint textureID=texture->getID();
        //Delete texture
        if( textureID != 0 )
        {
		glDeleteTextures( 1, &textureID );
		texture->setID(0);
        }

        texture->setWidth(0);
        texture->setHeight(0);
}

Uint32 GraphicsGL::getPixel(SDL_Surface *surface, int x,int y)
{
	int bpp=0;
	if(x>=0&&y>=0&&x<surface->w&&y<surface->h)
	{
		bpp=surface->format->BytesPerPixel;
	}
	else
	{
		std::cout<<"x= "<<x<<" y ="<<y<<" is out of bounds\n";
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
		std::cout<<"Error in reading pixel at x="<<x<<" y="<<y<<endl;
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}



bool GraphicsGL::updateTexture(Texture* texture)
{
	if(DEBUG)
		cout<<"unlock"<<endl;
	GLuint *mPixels= texture->getPixels();
	int mTextureWidth=texture->getWidth();
	int mTextureHeight=texture->getHeight();
	int mTextureID=texture->getID(); 
	//If texture is locked and a texture exists 
	if( mPixels != NULL && mTextureID != 0 ) 
	{ 
		//Set current texture 
		glBindTexture( GL_TEXTURE_2D, mTextureID ); 
		//Update texture 
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, mTextureWidth, mTextureHeight, GL_RGBA, GL_UNSIGNED_BYTE, mPixels ); 
		//Unbind texture 
		unbindTexture();
		return true; 
	}
	return false;
}

void GraphicsGL::addTexture(Texture *texture,Rects *clip)
{

}
